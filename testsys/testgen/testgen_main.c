#include <stdlib.h>
#include "../test_idents.h"
#include "testgen.h"

int main() {
    printf("\ngenerating autotests...\n");

    printf("\n- dead test");
    testDead();
    printf("\n- noise test");
    testNoise();
    printf("\n- whisper test");
    testWhisper();
    printf("\n- sets test (far)");
    testSetsFar();
    printf("\n- sets test (close)");
    testSetsClose();
    printf("\n- outburst test (close)");
    testOutburstsClose();
    printf("\n- outburst test (far)");
    testOutburstsFar();
    printf("\n- sets+outbursts test");
    testSetsOutbursts();
    printf("\n- base-pulse test");
    testBasePulse();
    printf("\n- diap-pulse test");
    testDiapPulse();

    printf("\n\ngenerating finished\n\n");
    return 0;
}
