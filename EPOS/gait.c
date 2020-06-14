
#include "gait.h"

double ang[51]  = {6.464,7.102,8.449,10.158,11.772,12.992,13.599,13.527,12.995,12.22,11.283,10.256,9.193,8.152,7.174,6.271,5.442,4.702,4.079,3.597,3.299,3.222,
    3.418,3.947,4.855,6.2,8.084,10.621,13.945,18.181,23.361,29.341,35.748,42.002,47.489,51.734,54.476,55.651,55.3,53.502,50.384,46.118,40.922,35.037,28.801,22.629,
16.957,12.215,8.741,6.708,6.017};

uint32_t angle_1[323] = {10682,10675,10669,10665,10664,10665,10668,10674,10683,10695,10711,10729,10751,10777,10807,10840,10878,10919,10965,11015,11070,11129,11192,11260,
    11333,11411,11493,11580,11672,11769,11870,11976,12086,12201,12321,12445,12573,12706,12843,12983,13128,13276,13428,13583,13741,13902,14066,14233,14401,14573,14745,
    14920,15096,15273,15451,15630,15809,15988,16167,16345,16523,16700,16875,17049,17220,17390,17557,17722,17883,18041,18195,18346,18492,18634,18772,18904,19032,19154,
    19270,19381,19486,19584,19676,19762,19841,19913,19978,20036,20086,20129,20165,20193,20214,20227,20232,20229,20219,20201,20175,20141,20100,20051,19995,19931,19859,
    19781,19695,19602,19503,19396,19283,19164,19039,18907,18770,18627,18479,18326,18167,18005,17838,17667,17492,17314,17132,16948,16760,16571,16380,16186,15992,15796,
    15600,15403,15206,15009,14812,14616,14421,14228,14036,13846,13658,13472,13289,13110,12933,12760,12590,12425,12263,12106,11953,11805,11662,11524,11391,11264,11142,
    11025,10914,10809,10710,10617,10530,10448,10373,10304,10240,10183,10132,10087,10048,10014,9987,9965,9948,9938,9932,9932,9937,9947,9962,9982,10006,10034,10067,10103,
    10143,10187,10234,10284,10337,10393,10451,10511,10573,10637,10703,10770,10837,10906,10975,11045,11114,11184,11253,11322,11389,11456,11522,11586,11649,11710,11769,
    11826,11881,11933,11983,12030,12075,12116,12155,12190,12222,12251,12277,12299,12318,12333,12345,12354,12359,12360,12358,12353,12344,12332,12316,12298,12276,12252,
    12224,12193,12160,12124,12086,12046,12003,11958,11911,11863,11813,11762,11709,11655,11601,11546,11490,11434,11377,11321,11265,11209,11154,11099,11046,10993,10942,
    10892,10844,10797,10752,10709,10669,10630,10594,10560,10529,10500,10475,10452,10432,10415,10401,10390,10382,10377,10375,10377,10381,10389,10400,10414,10431,10450,
    10473,10499,10527,10558,10591,10627,10665,10705,10748,10792,10839,10886,10936,10987,11039,11091,11145,11200,11255,11310,11366,11421,11476,11531,11586,11639,11692};
    
uint32_t angle_2[404] = {11744,11794,11843,11891,11936,11980,12022,12062,12099,12134,12166,12196,12223,12247,12268,12287,12302,12314,12323,12328,12331,12330,12326,12318,12307,12294,12276,
    12256,12233,12207,12177,12145,12110,12073,12033,11990,11946,11899,11850,11799,11747,11693,11638,11581,11524,11466,11407,11348,11289,11230,11171,11113,11055,10998,
    10942,10887,10834,10782,10732,10684,10638,10594,10553,10514,10479,10446,10416,10389,10366,10346,10329,10315,10306,10300,10297,10298,10303,10311,10323,10339,10358,
    10380,10406,10435,10467,10502,10540,10581,10624,10670,10718,10768,10819,10872,10926,10981,11037,11093,11150,11206,11262,11317,11371,11423,11474,11523,11569,11613,
    11654,11691,11725,11754,11779,11800,11815,11825,11830,11829,11821,11808,11787,11760,11726,11684,11635,11578,11514,11442,11361,11273,11176,11071,10958,10837,10708,
    10571,10425,10272,10112,9944,9768,9586,9397,9201,8999,8792,8579,8361,8139,7913,7683,7451,7216,6979,6741,6503,6265,6028,5793,5559,5329,5103,4882,4666,4457,4255,4061,
    3876,3702,3537,3385,3246,3120,3008,2912,2832,2770,2726,2701,2695,2711,2749,2809,2892,3000,3133,3292,3477,3690,3930,4200,4498,4827,5186,5576,5997,6450,6936,7454,
    8005,8589,9207,9858,10543,11262,12015,12801,13621,14474,15360,16280,17232,18217,19233,20281,21359,22468,23606,24773,25968,27191,28439,29713,31012,32334,33678,35044,
    36429,37834,39256,40694,42147,43613,45091,46580,48079,49584,51096,52612,54131,55651,57170,58688,60201,61709,63210,64702,66184,67653,69108,70548,71970,73373,74755,
    76115,77451,78761,80044,81299,82523,83715,84874,85999,87087,88138,89151,90123,91055,91944,92790,93591,94347,95057,95720,96335,96901,97418,97884,98301,98666,98980,
    99242,99453,99611,99717,99770,99771,99720,99617,99462,99255,98997,98689,98330,97921,97463,96957,96403,95803,95156,94465,93729,92951,92131,91270,90369,89430,88455,
    87444,86398,85320,84210,83071,81903,80708,79488,78245,76979,75693,74388,73065,71728,70376,69012,67637,66254,64863,63467,62067,60664,59260,57857,56457,55060,53669,
    52284,50908,49541,48185,46842,45512,44198,42899,41617,40354,39111,37888,36686,35507,34351,33219,32112,31030,29975,28947,27946,26972,26027,25111,24224,23366,22537,
    21738,20969,20230,19520,18841,18191,17570,16979,16417,15884,15380,14903,14455,14033,13639,13271,12929,12612,12319,12051,11805,11583,11382,11203,11043,10904,10784,
  10681,10596,10528,10475,10437,10413,10402,10404,10418,10442,10477,10520,10572,10632,10682};

/*int test_angle[24] = {	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
							500,0,
							(0.0),0.0,0.0,0.0,0.0,
							(0.0),0.0,0.0,0.0,0.0,
							0,500};
*/
int test_angle[114] = {500, 
1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
500,0, -500,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-500, 0};

int hip_0_5m[114] = {0, 15, 30, 60, 90, 135, 180, 240, 300, 375, 450, 540, 630, 735, 840, 960, 1080, 1215, 1350, 1500, 1650, 1815, 1980, 2145, 2310, 2475, 2640, 2805, 2970, 3120, 3270, 3405, 3540, 3660, 3780, 3885, 3990, 4080, 4170, 4230, 4290, 4335, 4380, 4410, 4440, 4455, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4466.5, 4463, 4453, 4443, 4433, 4423, 4413, 4403, 4393, 4383, 4358, 4333, 4278, 4223, 4118, 4013, 3858, 3703, 3498, 3293, 3038, 2783, 2478, 2173, 1818, 1463, 1058, 653, 198, -257, -737};
int hip_1_5m[204] = {-1217, -1697, -2177, -2656.5, -3136, -3616, -4096, -4575.5, -5055, -5535, -6015, -6494.5, -6974, -7454, -7934, -8413.5, -8893, -9373, -9853, -10332.5, -10812, -11292, -11772, -12251.5, -12731, -13211, -13691, -14170.5, -14650, -15130, -15610, -16089.5, -16569, -17049, -17529, -17984, -18439, -18844, -19249, -19604, -19959, -20264, -20569, -20824, -21079, -21284, -21489, -21644, -21799, -21904, -22009, -22064, -22119, -22124, -22129, -22084, -22039, -21944, -21849, -21704, -21559, -21364, -21169, -20924, -20679, -20384, -20089, -19744, -19399, -19004, -18609, -18164, -17719, -17224, -16729, -16184, -15639, -15044, -14449, -13804, -13159, -12464, -11769, -11024, -10279, -9509, -8739, -7969, -7199, -6454, -5709, -5014, -4319, -3674, -3029, -2434, -1839, -1294, -749, -254, 241, 729, 1217, 1697, 2177, 2656.5, 3136, 3616, 4096, 4575.5, 5055, 5535, 6015, 6494.5, 6974, 7454, 7934, 8413.5, 8893, 9373, 9853, 10332.5, 10812, 11292, 11772, 12251.5, 12731, 13211, 13691, 14170.5, 14650, 15130, 15610, 16089.5, 16569, 17049, 17529, 17984, 18439, 18844, 19249, 19604, 19959, 20264, 20569, 20824, 21079, 21284, 21489, 21644, 21799, 21904, 22009, 22064, 22119, 22124, 22129, 22084, 22039, 21944, 21849, 21704, 21559, 21364, 21169, 20924, 20679, 20384, 20089, 19744, 19399, 19004, 18609, 18164, 17719, 17224, 16729, 16184, 15639, 15044, 14449, 13804, 13159, 12464, 11769, 11024, 10279, 9509, 8739, 7969, 7199, 6454, 5709, 5014, 4319, 3674, 3029, 2434, 1839, 1294, 749, 254, -241, -729};

int hip_0_10m[57] = {0, 30, 90, 180, 300, 450, 630, 840, 1080, 1350, 1650, 1980, 2310, 2640, 2970, 3270, 3540, 3780, 3990, 4170, 4290, 4380, 4440, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4470, 4463, 4443, 4423, 4403, 4383, 4333, 4223, 4013, 3703, 3293, 2783, 2173, 1463, 653, -257};
int hip_1_10m[102] = {-1217 , -2177 , -3136 , -4096 , -5055 , -6015 , -6974 , -7934 , -8893 , -9853 , -10812 , -11772 , -12731 , -13691 , -14650 , -15610 , -16569 , -17529 , -18439 , -19249 , -19959 , -20569 , -21079 , -21489 , -21799 , -22009 , -22119 , -22129 , -22039 , -21849 , -21559 , -21169 , -20679 , -20089 , -19399 , -18609 , -17719 , -16729 , -15639 , -14449 , -13159 , -11769 , -10279 , -8739 , -7199 , -5709 , -4319 , -3029 , -1839 , -749 , 241 , 1217 , 2177 , 3136 , 4096 , 5055 , 6015 , 6974 , 7934 , 8893 , 9853 , 10812 , 11772 , 12731 , 13691 , 14650 , 15610 , 16569 , 17529 , 18439 , 19249 , 19959 , 20569 , 21079 , 21489 , 21799 , 22009 , 22119 , 22129 , 22039 , 21849 , 21559 , 21169 , 20679 , 20089 , 19399 , 18609 , 17719 , 16729 , 15639 , 14449 , 13159 , 11769 , 10279 , 8739 , 7199 , 5709 , 4319 , 3029 , 1839 , 749 , -241};

int hip_0_15m[38] = {30 , 135 , 300 , 540 , 840 , 1215 , 1650 , 2145 , 2640 , 3120 , 3540 , 3885 , 4170 , 4335 , 4440 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4470 , 4467 , 4443 , 4413 , 4383 , 4278 , 4013 , 3498 , 2783 , 1818 , 653 , -737};
int hip_1_15m[68] = {-2177 , -3616 , -5055 , -6495 , -7934 , -9373 , -10812 , -12252 , -13691 , -15130 , -16569 , -17984 , -19249 , -20264 , -21079 , -21644 , -22009 , -22124 , -22039 , -21704 , -21169 , -20384 , -19399 , -18164 , -16729 , -15044 , -13159 , -11024 , -8739 , -6454 , -4319 , -2434 , -749 , 729 , 2177 , 3616 , 5055 , 6495 , 7934 , 9373 , 10812 , 12252 , 13691 , 15130 , 16569 , 17984 , 19249 , 20264 , 21079 , 21644 , 22009 , 22124 , 22039 , 21704 , 21169 , 20384 , 19399 , 18164 , 16729 , 15044 , 13159 , 11024 , 8739 , 6454 , 4319 , 2434 , 749 , -729};


//---------------*/*|*\*——*/*|*\*——*/---------------*/*|*\*——*/*|*\*——*/---------------*/*|*\*——*/*|*\*——*/---------------*/*|*\*——*/*|*\*——*/------------------


int knee_0_5m[58] = {0 , -20 , -40 , -60 , -80 , -100 , -120 , -140 , -160 , -180 , -200 , -220 , -240 , -260 , -280 , -300 , -320 , -340 , -360 , -380 , -400 , -420 , -440 , -460 , -480 , -500 , -520 , -540 , -560 , -580 , -600 , -620 , -640 , -660 , -680 , -723 , -765 , -831 , -896 , -987 , -1078 , -1195 , -1311 , -1453 , -1595 , -1763 , -1930 , -2123 , -2316 , -2535 , -2753 , -2972 , -3190 , -3409 , -3627 , -3846 , -4064 , -4283};
int knee_1_5m[204] = {-4501 , -4720 , -4938 , -5157 , -5376 , -5595 , -5813 , -6032 , -6250 , -6469 , -6687 , -6906 , -7124 , -7343 , -7561 , -7780 , -7999 , -8218 , -8436 , -8655 , -8873 , -9092 , -9310 , -9529 , -9747 , -9966 , -10185 , -10404 , -10622 , -10841 , -11059 , -11278 , -11496 , -11715 , -11933 , -12152 , -12371 , -12590 , -12808 , -13027 , -13245 , -13464 , -13682 , -13901 , -14119 , -14338 , -14556 , -14775 , -14994 , -15213 , -15431 , -15585 , -15738 , -15827 , -15915 , -15939 , -15962 , -15921 , -15879 , -15773 , -15666 , -15495 , -15323 , -15087 , -14850 , -14549 , -14247 , -13881 , -13514 , -13083 , -12651 , -12155 , -11658 , -11097 , -10535 , -9909 , -9282 , -8591 , -7899 , -7143 , -6386 , -5610 , -4833 , -4082 , -3330 , -2644 , -1957 , -1336 , -714 , -158 , 399 , 891 , 1382 , 1809 , 2235 , 2597 , 2958 , 3255 , 3551 , 3808 , 4064 , 4283 , 4501 , 4720 , 4938 , 5157 , 5376 , 5595 , 5813 , 6032 , 6250 , 6469 , 6687 , 6906 , 7124 , 7343 , 7561 , 7780 , 7999 , 8218 , 8436 , 8655 , 8873 , 9092 , 9310 , 9529 , 9747 , 9966 , 10185 , 10404 , 10622 , 10841 , 11059 , 11278 , 11496 , 11715 , 11933 , 12152 , 12371 , 12590 , 12808 , 13027 , 13245 , 13464 , 13682 , 13901 , 14119 , 14338 , 14556 , 14775 , 14994 , 15213 , 15431 , 15585 , 15738 , 15827 , 15915 , 15939 , 15962 , 15921 , 15879 , 15773 , 15666 , 15495 , 15323 , 15087 , 14850 , 14549 , 14247 , 13881 , 13514 , 13083 , 12651 , 12155 , 11658 , 11097 , 10535 , 9909 , 9282 , 8591 , 7899 , 7143 , 6386 , 5610 , 4833 , 4082 , 3330 , 2644 , 1957 , 1336 , 714 , 158 , -399 , -891 , -1382 , -1809 , -2235 , -2597 , -2958 , -3255 , -3551 , -3808 , -4064 , -4283};

int knee_0_10m[29] = {0, -40, -80, -120, -160, -200, -240, -280, -320, -360, -400, -440, -480, -520, -560, -600, -640, -680, -765, -896, -1078, -1311, -1595, -1930, -2316, -2753, -3190, -3627, -4064};
int knee_1_10m[102] = {-4501, -4938, -5376, -5813, -6250, -6687, -7124, -7561, -7999, -8436, -8873, -9310, -9747, -10185, -10622, -11059, -11496, -11933, -12371, -12808, -13245, -13682, -14119, -14556, -14994, -15431, -15738, -15915, -15962, -15879, -15666, -15323, -14850, -14247, -13514, -12651, -11658, -10535, -9282, -7899, -6386, -4833, -3330, -1957, -714, 399, 1382, 2235, 2958, 3551, 4064, 4501, 4938, 5376, 5813, 6250, 6687, 7124, 7561, 7999, 8436, 8873, 9310, 9747, 10185, 10622, 11059, 11496, 11933, 12371, 12808, 13245, 13682, 14119, 14556, 14994, 15431, 15738, 15915, 15962, 15879, 15666, 15323, 14850, 14247, 13514, 12651, 11658, 10535, 9282, 7899, 6386, 4833, 3330, 1957, 714, -399, -1382, -2235, -2958, -3551, -4064};

int knee_0_15m[19] = {-60 , -120 , -180 , -240 , -300 , -360 , -420 , -480 , -540 , -600 , -660 , -765 , -987 , -1311 , -1763 , -2316 , -2972 , -3627 , -4283};
int knee_1_15m[68] = {-4938 , -5595 , -6250 , -6906 , -7561 , -8218 , -8873 , -9529 , -10185 , -10841 , -11496 , -12152 , -12808 , -13464 , -14119 , -14775 , -15431 , -15827 , -15962 , -15773 , -15323 , -14549 , -13514 , -12155 , -10535 , -8591 , -6386 , -4082 , -1957 , -158 , 1382 , 2597 , 3551 , 4283 , 4938 , 5595 , 6250 , 6906 , 7561 , 8218 , 8873 , 9529 , 10185 , 10841 , 11496 , 12152 , 12808 , 13464 , 14119 , 14775 , 15431 , 15827 , 15962 , 15773 , 15323 , 14549 , 13514 , 12155 , 10535 , 8591 , 6386 , 4082 , 1957 , 158 , -1382 , -2597 , -3551 , -4283};
