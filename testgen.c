#include "test_idents.h"
#include "testgen.h"

void testDead() {
    char file_name[48] = {};

    /* кэш бесполезен */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        FILE *dead = NULL;
        sprintf(file_name, "tests/%d-%d.tst", DEAD, iter);
        dead = fopen(file_name, "w");
        assert(dead);

        fprintf(dead, "%d 1000000\n", cache_size);
        for (int i = 0; i < 1000000; ++i) {
            fprintf(dead, "%d ", i);
        }

        fclose(dead);
    }
}

void testNoise() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 2;

    /* абсолютно случайные числа в широком диапазоне - должны
    плохо кэшироваться, но чуть лучше при увеличении размера кэша */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        FILE *noise = NULL;
        sprintf(file_name, "tests/%d-%d.tst", NOISE, iter);
        noise = fopen(file_name, "w");
        assert(noise);

        srand(seed);
        fprintf(noise, "%d 1000000\n", cache_size);
        for (int i = 0; i < 1000000; ++i) {
            fprintf(noise, "%d ", rand() % 20000);
        }

        fclose(noise);
    }
}

void testWhisper() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 15;

    /* то же, но в более узком диапазоне - после определенного размера
    кэшируется весь диапазон и хитрейт вырастет до ~100% */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        FILE *whisper = NULL;
        sprintf(file_name, "tests/%d-%d.tst", WHISPER, iter);
        whisper = fopen(file_name, "w");
        assert(whisper);

        srand(seed);
        fprintf(whisper, "%d 1000000\n", cache_size);
        for (int i = 0; i < 1000000; ++i) {
            fprintf(whisper, "%d ", rand() % 1000);
        }

        fclose(whisper);
    }
}

void testSetsFar() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 22;
    
    /* каждые 8000 +- 6000 реквестов сет реквестов меняется на почти
    точно совершенно другой (числа внутри сета близко стоящие, но это
    не важно), чисел внутри сета 400 +- 300 */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0;
        FILE *sets_far = NULL;
        sprintf(file_name, "tests/%d-%d.tst", SETS_F, iter);
        sets_far = fopen(file_name, "w");
        assert(sets_far);

        srand(seed);
        fprintf(sets_far, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int base = rand(), set = rand() % 600 + 100, dur = rand() % 12000 + 2000;
            if (base > INT_MAX - 1000) {
                base -= 1000;
            }

            for (int i = 0; i < dur && reqs + i < 1000000; ++i) {
                fprintf(sets_far, "%d ", rand() % set + base);
            }
            reqs += dur;
        }

        fclose(sets_far);
    }
}

void testSetsClose() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 86;
    
    /* почти то же самое, но теперь общий пул реквестов для разных сетов
    ограничен (т.к. base выбирается из малого диапазона), сеты чаще
    пересекаются, переходы становятся плавнее */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0;
        FILE *sets_close = NULL;
        sprintf(file_name, "tests/%d-%d.tst", SETS_C, iter);
        sets_close = fopen(file_name, "w");
        assert(sets_close);

        srand(seed);
        fprintf(sets_close, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int base = rand() % 800, set = rand() % 600 + 100, dur = rand() % 12000 + 2000;

            for (int i = 0; i < dur && reqs + i < 1000000; ++i) {
                fprintf(sets_close, "%d ", rand() % set + base);
            }
            reqs += dur;
        }

        fclose(sets_close);
    }
}

void testOutburstsClose() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 64;
    
    /* стандартный шум с диапазоном в 300 значений, каждые 2-8 происходит
    почти УНИКАЛЬНЫЙ реквест - аутберст - LFU эффект должен сгладить проблемы */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0;
        FILE *outbursts_close = NULL;
        sprintf(file_name, "tests/%d-%d.tst", OUTBURST_C, iter);
        outbursts_close = fopen(file_name, "w");
        assert(outbursts_close);

        srand(seed);
        fprintf(outbursts_close, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int timer = rand() % 7 + 1;
            fprintf(outbursts_close, "%d ", rand());
            reqs += 1;
            for (int i = 0; i < timer && reqs + i < 1000000; ++i) {
                fprintf(outbursts_close, "%d ", rand() % 300);
            }
            reqs += timer;
        }

        fclose(outbursts_close);
    }

}

void testOutburstsFar() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 112;
 
    /* то же самое, но аутберсты происходят только каждые 10-60 реквестов */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0;
        FILE *outbursts_far = NULL;
        sprintf(file_name, "tests/%d-%d.tst", OUTBURST_F, iter);
        outbursts_far = fopen(file_name, "w");
        assert(outbursts_far);

        srand(seed);
        fprintf(outbursts_far, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int timer = rand() % 51 + 9;
            fprintf(outbursts_far, "%d ", rand());
            reqs += 1;
            for (int i = 0; i < timer && reqs + i < 1000000; ++i) {
                fprintf(outbursts_far, "%d ", rand() % 300);
            }
            reqs += timer;
        }

        fclose(outbursts_far);
    }
}

void testSetsOutbursts() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 109;

    /* комбинация outbursts_close и sets_close */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0;
        FILE *set_burst = NULL;
        sprintf(file_name, "tests/%d-%d.tst", SETS_OUTBURSTS, iter);
        set_burst = fopen(file_name, "w");
        assert(set_burst);

        srand(seed);
        fprintf(set_burst, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int base = rand() % 800, set = rand() % 600 + 100, dur = rand() % 12000 + 2000, tick = 0, timer = 0;

            for (int i = 0; i < dur && reqs + i < 1000000; ++i, ++timer) {
                if (tick == timer) {
                    fprintf(set_burst, "%d ", rand());
                    tick = 0;
                    timer = rand() % 7 + 4;
                } else {
                    fprintf(set_burst, "%d ", rand() % set + base);
                }
            }
            reqs += dur;
        }

        fclose(set_burst);
    }
}

void testBasePulse() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 700;

    /* постепенное изменение вверх-вниз основания сета
    с постоянным диапазоном + аутберсты */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0, base = 0;
        bool up = true;
        FILE *grow_burst = NULL;
        sprintf(file_name, "tests/%d-%d.tst", BASE_PULSE, iter);
        grow_burst = fopen(file_name, "w");
        assert(grow_burst);

        srand(seed);
        fprintf(grow_burst, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int timer = rand() % 7 + 2;
            fprintf(grow_burst, "%d ", rand());
            reqs += 1;
            for (int i = 0; i < timer && reqs + i < 1000000; ++i) {
                fprintf(grow_burst, "%d ", rand() % 300 + base);
                if (up) {
                    base += rand() % 30 + 10;
                } else {
                    base -= rand() % 30 + 10;
                }
                if (base > 1200) {
                    up = false;
                }
                if (base < 100) {
                    up = true;
                }
            }
            reqs += timer;
        }

        fclose(grow_burst);
    }
}

void testDiapPulse() {
    char file_name[48] = {};
    unsigned seed = time(NULL) + 444;

    /* сеты с периодически меняющимся основанием и постепенно меняющимся
    вверх-вниз диапазоном */
    for (int cache_size = 4, iter = 0; cache_size < 17000; cache_size *= 2, ++iter) {
        int reqs = 0, set = 400;
        bool up = true;
        FILE *dyn_diap = NULL;
        sprintf(file_name, "tests/%d-%d.tst", DIAP_PULSE, iter);
        dyn_diap = fopen(file_name, "w");
        assert(dyn_diap);

        srand(seed);
        fprintf(dyn_diap, "%d 1000000\n", cache_size);
        while (reqs < 1000000) {
            int base = rand() % 900, dur = rand() % 12000 + 2000;
            
            for (int i = 0; i < dur && reqs + i < 1000000; ++i) {
                fprintf(dyn_diap, "%d ", rand() % set + base);
                if (up) {
                    set += rand() % 7 + 4;
                } else {
                    set -= rand() % 6 + 6;
                }
                if (set < 200) {
                    up = true;
                }
                if (set > 600) {
                    up = false;
                }
            }
            reqs += dur;
        }

        fclose(dyn_diap);
    }
}
