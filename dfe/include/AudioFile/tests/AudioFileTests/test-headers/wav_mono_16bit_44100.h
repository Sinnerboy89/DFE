#include <vector>

namespace wav_mono_16bit_44100 { 

int numSamplesPerChannel = 352800;
int bitDepth = 16;
uint32_t sampleRate = 44100;
int numChannels = 1;

std::vector<double> testBuffer = {-3.0517578125e-05, -0.0001220703125, -0.001251220703125, -0.002655029296875, -0.003082275390625, 0.00384521484375, 0.02276611328125, 0.032806396484375, 0.02392578125, -0.006927490234375, -0.044647216796875, -0.03363037109375, 0.013580322265625, 0.030853271484375, 0.017547607421875, 0.00823974609375, 0.004669189453125, -0.00555419921875, -0.0089111328125, -0.014495849609375, -0.01409912109375, -0.04644775390625, -0.087615966796875, -0.070159912109375, -0.066192626953125, -0.03851318359375, 0.079010009765625, -0.015350341796875, 0.08154296875, 0.04486083984375, 0.1390380859375, 0.130859375, 0.13897705078125, 0.170257568359375, 0.177337646484375, 0.200958251953125, 0.1513671875, 0.172027587890625, 0.06463623046875, 0.018524169921875, -0.0003662109375, -0.040283203125, 0.0504150390625, 0.1331787109375, -0.0211181640625, 0.0137939453125, -0.061004638671875, 0.03656005859375, 0.14935302734375, -0.0780029296875, -0.030181884765625, -0.13665771484375, 0.083526611328125, 0.14727783203125, 0.075286865234375, 0.043701171875, 0.04949951171875, 0.259674072265625, 0.239288330078125, 0.32977294921875, 0.241302490234375, 0.261627197265625, 0.145355224609375, 0.16058349609375, 0.23248291015625, 0.09307861328125, 0.117095947265625, 0.01812744140625, 0.08355712890625, 0.208099365234375, 0.23675537109375, 0.148284912109375, 0.197235107421875, 0.167083740234375, 0.1513671875, 0.0177001953125, -0.095672607421875, 0.00750732421875, -0.12213134765625, 0.01165771484375, 0.134368896484375, 0.1112060546875, 0.019775390625, 0.019287109375, 0.140533447265625, 0.315887451171875, 0.263671875, 0.111663818359375, 0.12506103515625, 0.083709716796875, 0.076751708984375, -0.1580810546875, -0.16351318359375, -0.114227294921875, -0.08740234375, 0.03411865234375, 0.100738525390625, 0.043792724609375, 0.1314697265625, 0.170318603515625, 0.1011962890625, 0.285430908203125, 0.0733642578125, 0.17108154296875, 0.169342041015625, 0.201751708984375, 0.209381103515625, -0.068695068359375, -0.00189208984375, -0.048553466796875, -0.002410888671875, -0.113494873046875, -0.08819580078125, -0.159271240234375, -0.11395263671875, -0.0447998046875, -0.076934814453125, 0.038970947265625, -0.08612060546875, -0.12738037109375, -0.132049560546875, -0.071685791015625, -0.06298828125, 0.072174072265625, 0.043243408203125, 0.007568359375, -0.112457275390625, -0.235748291015625, -0.246368408203125, -0.339935302734375, -0.268218994140625, -0.31976318359375, -0.125457763671875, -0.166229248046875, -0.169342041015625, -0.165557861328125, -0.165771484375, -0.108154296875, -0.197784423828125, -0.05487060546875, -0.187103271484375, -0.0615234375, -0.077484130859375, -0.140899658203125, -0.017364501953125, -0.040069580078125, 0.063690185546875, 0.06719970703125, 0.06475830078125, 0.032562255859375, 0.03277587890625, -0.020660400390625, -0.0535888671875, -0.097900390625, -0.1622314453125, -0.149749755859375, -0.14080810546875, -0.1466064453125, -0.172393798828125, -0.20135498046875, -0.15380859375, -0.077911376953125, -0.14532470703125, -0.114990234375, -0.110107421875, -0.087249755859375, -0.079376220703125, -0.099761962890625, -0.044403076171875, -0.052398681640625, -0.05029296875, -0.087615966796875, -0.118804931640625, -0.11163330078125, -0.091033935546875, -0.074859619140625, -0.058197021484375, -0.12762451171875, -0.08990478515625, -0.052398681640625, -0.050567626953125, -0.067047119140625, -0.115203857421875, -0.04034423828125, -0.054412841796875, 0.00579833984375, 0.04461669921875, 0.1109619140625, 0.163970947265625, 0.249969482421875, 0.233154296875, 0.126220703125, 0.254669189453125, 0.20391845703125, 0.18463134765625, 0.14215087890625, 0.053375244140625, 0.025787353515625, 0.011260986328125, -0.00982666015625, -0.040985107421875, -0.039093017578125, -0.04107666015625, 0.0111083984375, -0.042633056640625, 0.018280029296875, -0.01263427734375, -0.032440185546875, 0.087493896484375, 0.089385986328125, 0.0784912109375, 0.095489501953125, 0.125396728515625, 0.07867431640625, 0.109405517578125, 0.113433837890625, 0.100341796875, 0.098480224609375, 0.13330078125, 0.127777099609375, 0.0899658203125, 0.091033935546875, -0.0078125, 0.000946044921875, -0.027252197265625, -0.080718994140625, -0.082244873046875, -0.039581298828125, 0.011260986328125, -0.0389404296875, -0.069580078125, -0.035614013671875, 0.00152587890625, 0.039520263671875, 0.08514404296875, 0.023284912109375, 0.035247802734375, 0.055084228515625, 0.064361572265625, 0.10723876953125, 0.067230224609375, 0.121002197265625, 0.124298095703125, 0.124237060546875, 0.168914794921875, 0.125244140625, 0.145721435546875, 0.1474609375, 0.110626220703125, 0.08642578125, 0.05352783203125, 0.090911865234375, 0.1287841796875, 0.094451904296875, 0.071075439453125, 0.073577880859375, 0.036285400390625, 0.031402587890625, 0.025360107421875, 0.029571533203125, -0.00909423828125, -0.032989501953125, -0.02886962890625, -0.080413818359375, -0.02471923828125, -0.0498046875, -0.069122314453125, -0.06512451171875, -0.054931640625, -0.085296630859375, -0.101531982421875, -0.0321044921875, -0.068634033203125, -0.040435791015625, -0.1119384765625, -0.07354736328125, -0.0289306640625, -0.00732421875, -0.004608154296875, -0.037261962890625, 0.025726318359375, -0.076171875, -0.030426025390625, -0.03961181640625, 0.0057373046875, -0.006256103515625, -0.04412841796875, 0.003082275390625, -0.1204833984375, -0.090789794921875, -0.074981689453125, -0.063934326171875, -0.10467529296875, -0.133026123046875, -0.1632080078125, -0.13623046875, -0.151519775390625, -0.208465576171875, -0.132965087890625, -0.143890380859375, -0.152862548828125, -0.16778564453125, -0.08392333984375, -0.1307373046875, -0.16351318359375, -0.1253662109375, -0.1890869140625, -0.19110107421875, -0.175323486328125, -0.10791015625, -0.107330322265625, -0.127532958984375, -0.08636474609375, -0.115692138671875, -0.12982177734375, -0.10577392578125, -0.16046142578125, -0.080841064453125, -0.1798095703125, -0.21697998046875, -0.139892578125, -0.14263916015625, -0.10260009765625, -0.204376220703125, -0.10614013671875, -0.15338134765625, -0.106536865234375, -0.061859130859375, -0.020843505859375, 0.046478271484375, 0.009552001953125, 0.153717041015625, 0.0352783203125, 0.136566162109375, 0.116912841796875, 0.128326416015625, 0.154541015625, 0.01678466796875, 0.0965576171875, 0.057830810546875, 0.154266357421875, 0.115325927734375, 0.07916259765625, 0.126068115234375, 0.06011962890625, 0.051483154296875, 0.06878662109375, 0.047393798828125, 0.059906005859375, -0.018707275390625, -0.022064208984375, 0.0264892578125, -0.020355224609375, 0.04156494140625, -0.001739501953125, 0.0784912109375, 0.01312255859375, 0.0772705078125, 0.13177490234375, 0.009033203125, 0.064544677734375, -0.021148681640625, 0.04193115234375, 0.0037841796875, -0.0091552734375, 0.03631591796875, 0.061859130859375, 0.071258544921875, 0.010162353515625, 0.026885986328125, 0.042266845703125, 0.01922607421875, -0.022613525390625, 0.0460205078125, 0.031341552734375, 0.033538818359375, 0.014251708984375, 0.01312255859375, 0.010284423828125, 0.00469970703125, -0.01556396484375, 0.062286376953125, 0.085968017578125, 0.09210205078125, 0.201751708984375, 0.007476806640625, 0.08587646484375, 0.015777587890625, 0.0203857421875, 0.106353759765625, -0.019561767578125, 0.097381591796875, 0.09967041015625, 0.057342529296875, 0.000701904296875, 0.041290283203125, 0.02935791015625, 0.126434326171875, 0.05072021484375, 0.079559326171875, 0.16424560546875, 0.085968017578125, 0.180694580078125, 0.13385009765625, 0.1304931640625, 0.02130126953125, 0.134429931640625, 0.046234130859375, -0.004425048828125, 0.01910400390625, -0.038604736328125, 0.040802001953125, -0.093536376953125, -0.070404052734375, -0.09259033203125, -0.01220703125, -0.063751220703125, -0.0347900390625, 0.033111572265625, 0.01263427734375, 0.02178955078125, -0.035491943359375, 0.066558837890625, 0.004791259765625, 0.02777099609375, 0.014129638671875, -0.073516845703125, -0.098846435546875, -0.0360107421875, -0.0831298828125, -0.09454345703125, -0.12896728515625, -0.15985107421875, -0.059417724609375, -0.185394287109375, -0.12420654296875, -0.19830322265625, -0.125274658203125, -0.12945556640625, -0.2213134765625, -0.095977783203125, -0.159637451171875, -0.096466064453125, -0.13299560546875, -0.119171142578125, -0.088775634765625, -0.08599853515625, -0.1082763671875, -0.08697509765625, -0.0390625, -0.108489990234375, -0.06884765625, -0.076690673828125, -0.10101318359375, -0.116058349609375, -0.097747802734375, -0.0970458984375, -0.16552734375, -0.170654296875, -0.123992919921875, -0.179107666015625, -0.132415771484375, -0.12921142578125, -0.126708984375, -0.052337646484375, -0.12774658203125, -0.05712890625, -0.055755615234375, -0.043853759765625, -0.05029296875, -0.04345703125, -0.010162353515625, -0.05126953125, -0.0245361328125, -0.05657958984375, -0.01922607421875, -0.0189208984375, 0.00103759765625, 0.001068115234375, -0.010498046875, 0.02166748046875, 0.03521728515625, 0.021820068359375, -0.000579833984375, -0.051055908203125, -0.098114013671875, -0.046630859375, -0.090850830078125, -0.047882080078125, -0.052764892578125, -0.1024169921875, -0.06805419921875, -0.05572509765625, -0.0196533203125, 0.0538330078125, 0.051605224609375, -0.02459716796875, -0.003875732421875, -0.027984619140625, 0.0260009765625};

}; // end namespace