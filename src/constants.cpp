#include "constants.h"

namespace constants {

    extern const byte BRIGHTNESS_POT_PIN = A4;
    extern const byte POT_0_PIN = A3;
    extern const byte POT_1_PIN = A2;
    extern const byte POT_2_PIN = A1;
    extern const byte POT_3_PIN = A0;
    extern const byte BUTTON_0_PIN = 4;
    extern const byte BUTTON_1_PIN = 5;
    extern const byte BUTTON_2_PIN = 6;

    extern const byte MODE_CHANGE_PIN = 3;

    #ifdef OUTPUT_SUIT

        ////////////////////////////////////
        // SUIT (366 LEDS)                //
        ////////////////////////////////////

        extern const byte GRID_WIDTH = 10;
        extern const byte GRID_HEIGHT = 45;

        extern const byte HORIZ_TOP_LEFT_ROW = 0;
        extern const byte HORIZ_TOP_LEFT_COLUMN = 0;
        extern const byte HORIZ_DISPLAY_WIDTH = 10;
        extern const byte VERT_TOP_LEFT_ROW = 0;
        extern const byte VERT_TOP_LEFT_COLUMN = 8;
        extern const byte VERT_DISPLAY_WIDTH = 44;

        extern const int LED_GRID_INDECIES[GRID_WIDTH*GRID_HEIGHT] PROGMEM = {
            0,   26,  27,  59,  60,  305, 306, 338, 339, 365,
            1,   25,  28,  58,  61,  304, 307, 337, 340, 364,
            2,   24,  29,  57,  62,  303, 308, 336, 341, 363,
            3,   23,  30,  56,  63,  302, 309, 335, 342, 362,
            4,   22,  31,  55,  64,  301, 310, 334, 343, 361,
            5,   21,  32,  54,  65,  300, 311, 333, 344, 360,
            6,   20,  33,  53,  66,  299, 312, 332, 345, 359,
            7,   19,  34,  52,  67,  298, 313, 331, 346, 358,
            8,   18,  35,  51,  68,  297, 314, 330, 347, 357,
            9,   17,  36,  50,  69,  296, 315, 329, 348, 356,
            10,  16,  37,  49,  70,  295, 316, 328, 349, 355,
            11,  15,  38,  48,  71,  294, 317, 327, 350, 354,
            -1,  14,  39,  47,  72,  293, 318, 326, 351, -1,
            -1,  13,  40,  46,  73,  292, 319, 325, 352, -1,
            -1,  12,  41,  45,  74,  291, 320, 324, 353, -1,
            -1,  -1,  42,  44,  75,  290, 321, 323, -1,  -1,
            -1,  -1,  -1,  43,  76,  289, 322, -1,  -1,  -1,
            -1,  -1,  -1,  -1,  77,  288, -1,  -1,  -1,  -1,
            -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            116, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  221,
            117, 115, -1,  -1,  -1,  -1,  -1,  -1,  220, 222,
            118, 114, 95,  -1,  -1,  -1,  -1,  200, 219, 223,
            119, 113, 96,  94,  -1,  -1,  199, 201, 218, 224,
            120, 112, 97,  93,  78,  183, 198, 202, 217, 225,
            121, 111, 98,  92,  79,  184, 197, 203, 216, 226,
            122, 110, 99,  91,  80,  185, 196, 204, 215, 227,
            123, 109, 100, 90,  81,  186, 195, 205, 214, 228,
            124, 108, 101, 89,  82,  187, 194, 206, 213, 229,
            125, 107, 102, 88,  83,  188, 193, 207, 212, 230,
            126, 106, 103, 87,  84,  189, 192, 208, 211, 231,
            127, 105, 104, 86,  85,  190, 191, 209, 210, 232,
            -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            128, 149, 150, 171, 172, 277, 276, 255, 254, 233,
            129, 148, 151, 170, 173, 278, 275, 256, 253, 234,
            130, 147, 152, 169, 174, 279, 274, 257, 252, 235,
            131, 146, 153, 168, 175, 280, 273, 258, 251, 236,
            132, 145, 154, 167, 176, 281, 272, 259, 250, 237,
            133, 144, 155, 166, 177, 282, 271, 260, 249, 238,
            134, 143, 156, 165, 178, 283, 270, 261, 248, 239,
            135, 142, 157, 164, 179, 284, 269, 262, 247, 240,
            136, 141, 158, 163, 180, 285, 268, 263, 246, 241,
            137, 140, 159, 162, 181, 286, 267, 264, 245, 242,
            138, 139, 160, 161, 182, 287, 266, 265, 244, 243
        };


        // 255, 249, 244, 238, 233, 227, 222, 216, 211, 205, 200, 194, 188, 183, 177, 172, 166, 161, 155, 150, 144, 139, 133, 128, 122, 116, 111, 105, 100, 94,  89,  83,  78,  72,  67,  61,  55,  50,  44,  39,  33,  28,  22,  17,  11,  6,   0 
        // 0,   6,   11,  17,  22,  28,  33,  39,  44,  50,  55,  61,  67,  72,  78,  83,  89,  94,  100, 105, 111, 116, 122, 128, 133, 139, 144, 150, 155, 161, 166, 172, 177, 183, 188, 194, 200, 205, 211, 216, 222, 227, 233, 238, 244, 249, 255
        extern const byte LED_X_VALS[NUM_LEDS] PROGMEM = {
        //  0    1    2    3    4    5    6    7    8    9
            101, 101, 101, 101, 101, 101, 101, 101, 101, 101,

        //  10   11   12   13   14   15   16   17   18   19
            101, 101, 107, 107, 107, 107, 107, 107, 107, 107, 

        //  20   21   22   23   24   25   26   27   28   29   
            101, 101, 107, 107, 107, 107, 107, 113, 113, 113, 

        //  30   31   32   33   34   35   36   37   38   39   
            113, 113, 113, 113, 113, 113, 113, 113, 113, 113,

        //  40   41   42   43   44   45   46   47   48   49   
            113, 113, 113, 119, 119, 119, 119, 119, 119, 119,

        //  50   51   52   53   54   55   56   57   58   59   
            113, 113, 113, 119, 119, 119, 119, 119, 119, 119,

        //  60   61   62   63   64   65   66   67   68   69   
            125, 125, 125, 125, 125, 125, 125, 125, 125, 125,

        //  70   71   72   73   74   75   76   77   78   79   
            125, 125, 125, 125, 125, 125, 125, 125, 125, 125,

        //  80   81   82   83   84   85   86   87   88   89   
            125, 125, 125, 125, 125, 125, 119, 119, 119, 119,

        //  90   91   92   93   94   95   96   97   98   99   
            125, 125, 125, 125, 125, 113, 113, 113, 113, 113,




        //  100  101  102  103  104  105  106  107  108  109  
            113, 113, 113, 113, 113, 107, 107, 107, 107, 107,

        //  110  111  112  113  114  115  116  117  118  119  
            107, 107, 107, 107, 107, 107, 101, 101, 101, 101,

        //  120  121  122  123  124  125  126  127  128  129  
            101, 101, 101, 101, 101, 101, 101, 101, 101, 101,

        //  130  131  132  133  134  135  136  137  138  139  
            101, 101, 101, 101, 101, 101, 101, 101, 101, 107,

        //  140  141  142  143  144  145  146  147  148  149  
            107, 107, 107, 107, 107, 107, 107, 107, 107, 107,

        //  150  151  152  153  154  155  156  157  158  159  
            113, 113, 113, 113, 113, 113, 113, 113, 113, 113,

        //  160  161  162  163  164  165  166  167  168  169  
            113, 119, 119, 119, 119, 119, 119, 119, 119, 119,

        //  170  171  172  173  174  175  176  177  178  179  
            119, 119, 125, 125, 125, 125, 125, 125, 125, 125,

        //  180  181  182  183  184  185  186  187  188  189  
            113, 119, 119, 131, 131, 131, 131, 131, 131, 131,

        //  190  191  192  193  194  195  196  197  198  199  
            131, 137, 137, 137, 137, 137, 137, 137, 137, 137,




        //  200  201  202  203  204  205  206  207  208  209  
            143, 143, 143, 143, 143, 143, 143, 143, 143, 143,

        //  210  211  212  213  214  215  216  217  218  219  
            149, 149, 149, 149, 149, 149, 149, 149, 149, 149,

        //  220  221  222  223  224  225  226  227  228  229  
            149, 155, 155, 155, 155, 155, 155, 155, 155, 155,

        //  230  231  232  233  234  235  236  237  238  239  
            155, 155, 155, 155, 155, 155, 155, 155, 155, 155,

        //  240  241  242  243  244  245  246  247  248  249  
            155, 155, 155, 155, 149, 149, 149, 149, 149, 149,

        //  250  251  252  253  254  255  256  257  258  259  
            149, 149, 149, 149, 149, 143, 143, 143, 143, 143,

        //  260  261  262  263  264  265  266  267  268  269  
            143, 143, 143, 143, 143, 143, 137, 137, 137, 137,

        //  270  271  272  273  274  275  276  277  278  279  
            137, 137, 137, 137, 137, 137, 137, 131, 131, 131,

        //  280  281  282  283  284  285  286  287  288  289  
            131, 131, 131, 131, 131, 131, 131, 131, 131, 131,

        //  290  291  292  293  294  295  296  297  298  299  
            131, 131, 131, 131, 131, 131, 131, 131, 131, 131,




        //  300  301  302  303  304  305  306  307  308  309  
            143, 143, 143, 143, 143, 143, 137, 137, 137, 137,

        //  310  311  312  313  314  315  316  317  318  319  
            137, 137, 137, 137, 137, 137, 137, 137, 137, 137,

        //  320  321  322  323  324  325  326  327  328  329  
            137, 137, 137, 143, 143, 143, 143, 143, 143, 143,

        //  330  331  332  333  334  335  336  337  338  339  
            143, 143, 143, 143, 143, 143, 143, 143, 143, 149,

        //  340  341  342  343  344  345  346  347  348  349  
            149, 149, 149, 149, 149, 149, 149, 149, 149, 149,

        //  350  351  352  353  354  355  356  357  358  359  
            149, 149, 149, 149, 155, 155, 155, 155, 155, 155,

        //  360  361  362  363  364  365
            155, 155, 155, 155, 155, 155
        };


        extern const byte LED_Y_VALS[NUM_LEDS] PROGMEM = {
        //  0    1    2    3    4    5    6    7    8    9
            255, 249, 244, 238, 233, 227, 222, 216, 211, 205,

        //  10   11   12   13   14   15   16   17   18   19
            200, 194, 177, 183, 188, 194, 200, 205, 211, 216,

        //  20   21   22   23   24   25   26   27   28   29   
            222, 227, 233, 238, 244, 249, 255, 255, 249, 244,

        //  30   31   32   33   34   35   36   37   38   39   
            238, 233, 227, 222, 216, 211, 205, 200, 194, 188,

        //  40   41   42   43   44   45   46   47   48   49   
            183, 177, 172, 166, 172, 177, 183, 188, 194, 200,

        //  50   51   52   53   54   55   56   57   58   59   
            205, 211, 216, 222, 227, 233, 238, 244, 249, 255,

        //  60   61   62   63   64   65   66   67   68   69   
            255, 249, 244, 238, 233, 227, 222, 216, 211, 205,

        //  70   71   72   73   74   75   76   77   78   79   
            200, 194, 188, 183, 177, 172, 166, 161, 122, 116, 

        //  80   81   82   83   84   85   86   87   88   89   
            111, 105, 100, 94,  89,  83,  83,  89,  94,  100, 

        //  90   91   92   93   94   95   96   97   98   99   
            105, 111, 116, 122, 128, 133, 128, 122, 116, 111, 





        //  100  101  102  103  104  105  106  107  108  109  
            105, 100, 94,  89,  83,  83,  89,  94,  100, 105, 

        //  110  111  112  113  114  115  116  117  118  119  
            111, 116, 122, 128, 133, 139, 144, 139, 133, 128, 

        //  120  121  122  123  124  125  126  127  128  129  
            122, 116, 111, 105, 100, 94,  89,  83,  55,  50,

        //  130  131  132  133  134  135  136  137  138  139  
            44,  39,  33,  28,  22,  17,  11,  6,   0,   0,

        //  140  141  142  143  144  145  146  147  148  149  
            6,   11,  17,  22,  28,  33,  39,  44,  50,  55,

        //  150  151  152  153  154  155  156  157  158  159  
            55,  50,  44,  39,  33,  28,  22,  17,  11,  6,

        //  160  161  162  163  164  165  166  167  168  169  
            0,   6,   11,  17,  22,  28,  33,  39,  44,  50,

        //  170  171  172  173  174  175  176  177  178  179  
            50,  55,  55,  50,  44,  39,  33,  28,  22,  17,  

        //  180  181  182  183  184  185  186  187  188  189  
            11,  6,   0,   122, 116, 111, 105, 100, 94,  89,

        //  190  191  192  193  194  195  196  197  198  199  
            83,  83,  89,  94,  100, 105, 111, 116, 122, 128,





        //  200  201  202  203  204  205  206  207  208  209  
            133, 128, 122, 116, 111, 105, 100, 94,  89,  83,

        //  210  211  212  213  214  215  216  217  218  219  
            83,  89,  94,  100, 105, 111, 116, 122, 128, 133,

        //  220  221  222  223  224  225  226  227  228  229  
            139, 144, 139, 133, 128, 122, 116, 111, 105, 100,

        //  230  231  232  233  234  235  236  237  238  239  
            94,  89,  83,  55,  50,  44,  39,  33,  28,  22,  

        //  240  241  242  243  244  245  246  247  248  249  
            17,  11,  6,   0,   0,   6,   11,  17,  22,  28,

        //  250  251  252  253  254  255  256  257  258  259  
            33,  39,  44,  50,  55,  55,  50,  44,  39,  33, 

        //  260  261  262  263  264  265  266  267  268  269  
            28,  22,  17,  11,  6,   0,   0,   6,   11,  17, 

        //  270  271  272  273  274  275  276  277  278  279  
            22,  28,  33,  39,  44,  50,  55,  55,  50,  44,

        //  280  281  282  283  284  285  286  287  288  289  
            39,  33,  28,  22,  17,  11,  6,   0,   161, 166,

        //  290  291  292  293  294  295  296  297  298  299  
            172, 177, 183, 188, 194, 200, 205, 211, 216, 222,





        //  300  301  302  303  304  305  306  307  308  309  
            227, 233, 238, 244, 249, 255, 255, 249, 244, 238,

        //  310  311  312  313  314  315  316  317  318  319  
            233, 227, 222, 216, 211, 205, 200, 194, 188, 183,

        //  320  321  322  323  324  325  326  327  328  329  
            177, 172, 166, 172, 177, 183, 188, 194, 200, 205,

        //  330  331  332  333  334  335  336  337  338  339  
            211, 216, 222, 227, 233, 238, 244, 249, 255, 255,

        //  340  341  342  343  344  345  346  347  348  349  
            249, 244, 238, 233, 227, 222, 216, 211, 205, 200,

        //  350  351  352  353  354  355  356  357  358  359  
            194, 188, 183, 177, 194, 200, 205, 211, 216, 222,

        //  360  361  362  363  364  365
            227, 233, 238, 244, 249, 255
        };

    #endif

    ////////////////////////////////////
    // 8x8 GRID (64 LEDs)             //
    ////////////////////////////////////

    #ifdef OUTPUT_64_GRID

        extern const byte GRID_WIDTH = 8;
        extern const byte GRID_HEIGHT = 8;

        extern const byte HORIZ_TOP_LEFT_ROW = 0;
        extern const byte HORIZ_TOP_LEFT_COLUMN = 0;
        extern const byte HORIZ_DISPLAY_WIDTH = 8;
        extern const byte VERT_TOP_LEFT_ROW = 0;
        extern const byte VERT_TOP_LEFT_COLUMN = 7;
        extern const byte VERT_DISPLAY_WIDTH = 12;

        extern const int LED_GRID_INDECIES[NUM_LEDS] PROGMEM = {
            0,   1,   2,   3,   4,   5,   6,   7,
            8,   9,   10,  11,  12,  13,  14,  15,
            16,  17,  18,  19,  20,  21,  22,  23,
            24,  25,  26,  27,  28,  29,  30,  31,
            32,  33,  34,  35,  36,  37,  38,  39,
            40,  41,  42,  43,  44,  45,  46,  47,
            48,  49,  50,  51,  52,  53,  54,  55,
            56,  57,  58,  59,  60,  61,  62,  63
        };


        extern const byte LED_X_VALS[NUM_LEDS] PROGMEM = {
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255,
            0,   36,  79,  109, 146, 182, 218, 255
        };

        extern const byte LED_Y_VALS[NUM_LEDS] PROGMEM = {
            255, 255, 255, 255, 255, 255, 255, 255,   
            218, 218, 218, 218, 218, 218, 218, 218,   
            182, 182, 182, 182, 182, 182, 182, 182,   
            146, 146, 146, 146, 146, 146, 146, 146,   
            109, 109, 109, 109, 109, 109, 109, 109,   
            79,  79,  79,  79,  79,  79,  79,  79,    
            36,  36,  36,  36,  36,  36,  36,  36,    
            0,   0,   0,   0,   0,   0,   0,   0
        };

    #endif

    ////////////////////////////////////
    // 16x16 GRID (256 LEDs)          //
    ////////////////////////////////////

    #ifdef OUTPUT_256_GRID

        extern const byte GRID_WIDTH = 16;
        extern const byte GRID_HEIGHT = 16;

        extern const byte HORIZ_TOP_LEFT_ROW = 1;
        extern const byte HORIZ_TOP_LEFT_COLUMN = 1;
        extern const byte HORIZ_DISPLAY_WIDTH = 8;
        extern const byte VERT_TOP_LEFT_ROW = 1;
        extern const byte VERT_TOP_LEFT_COLUMN = 8;
        extern const byte VERT_DISPLAY_WIDTH = 12;

        extern const int LED_GRID_INDECIES[NUM_LEDS] PROGMEM = {
            15,  14,  13,  12,     11,  10,  9,   8,      7,   6,   5,   4,      3,   2,   1,   0,
            16,  17,  18,  19,     20,  21,  22,  23,     24,  25,  26,  27,     28,  29,  30,  31,
            47,  46,  45,  44,     43,  42,  41,  40,     39,  38,  37,  36,     35,  34,  33,  32,
            48,  49,  50,  51,     52,  53,  54,  55,     56,  57,  58,  59,     60,  61,  62,  63,

            79,  78,  77,  76,     75,  74,  73,  72,     71,  70,  69,  68,     67,  66,  65,  64,
            80,  81,  82,  83,     84,  85,  86,  87,     88,  89,  90,  91,     92,  93,  94,  95,
            111, 110, 109, 108,    107, 106, 105, 104,    103, 102, 101, 100,    99,  98,  97,  96,
            112, 113, 114, 115,    116, 117, 118, 119,    120, 121, 122, 123,    124, 125, 126, 127,

            143, 142, 141, 140,    139, 138, 137, 136,    135, 134, 133, 132,    131, 130, 129, 128,
            144, 145, 146, 147,    148, 149, 150, 151,    152, 153, 154, 155,    156, 157, 158, 159,
            175, 174, 173, 172,    171, 170, 169, 168,    167, 166, 165, 164,    163, 162, 161, 160,
            176, 177, 178, 179,    180, 181, 182, 183,    184, 185, 186, 187,    188, 189, 190, 191,

            207, 206, 205, 204,    203, 202, 201, 200,    199, 198, 197, 196,    195, 194, 193, 192,
            208, 209, 210, 211,    212, 213, 214, 215,    216, 217, 218, 219,    220, 221, 222, 223,
            239, 238, 237, 236,    235, 234, 233, 232,    231, 230, 229, 228,    227, 226, 225, 224,
            240, 241, 242, 243,    244, 245, 246, 247,    248, 249, 250, 251,    252, 253, 254, 255
            };

        extern const byte LED_X_VALS[NUM_LEDS] PROGMEM = {
            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,

            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,

            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,

            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
            0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
            255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0
        };

        extern const byte LED_Y_VALS[NUM_LEDS] PROGMEM = {
            255, 255, 255, 255,    255, 255, 255, 255,    255, 255, 255, 255,    255, 255, 255, 255,
            238, 238, 238, 238,    238, 238, 238, 238,    238, 238, 238, 238,    238, 238, 238, 238,
            221, 221, 221, 221,    221, 221, 221, 221,    221, 221, 221, 221,    221, 221, 221, 221,
            204, 204, 204, 204,    204, 204, 204, 204,    204, 204, 204, 204,    204, 204, 204, 204,

            187, 187, 187, 187,    187, 187, 187, 187,    187, 187, 187, 187,    187, 187, 187, 187,
            170, 170, 170, 170,    170, 170, 170, 170,    170, 170, 170, 170,    170, 170, 170, 170,
            153, 153, 153, 153,    153, 153, 153, 153,    153, 153, 153, 153,    153, 153, 153, 153,
            136, 136, 136, 136,    136, 136, 136, 136,    136, 136, 136, 136,    136, 136, 136, 136,

            119, 119, 119, 119,    119, 119, 119, 119,    119, 119, 119, 119,    119, 119, 119, 119,
            102, 102, 102, 102,    102, 102, 102, 102,    102, 102, 102, 102,    102, 102, 102, 102,
            85,  85,  85,  85,     85,  85,  85,  85,     85,  85,  85,  85,     85,  85,  85,  85, 
            68,  68,  68,  68,     68,  68,  68,  68,     68,  68,  68,  68,     68,  68,  68,  68, 

            51,  51,  51,  51,     51,  51,  51,  51,     51,  51,  51,  51,     51,  51,  51,  51, 
            34,  34,  34,  34,     34,  34,  34,  34,     34,  34,  34,  34,     34,  34,  34,  34, 
            17,  17,  17,  17,     17,  17,  17,  17,     17,  17,  17,  17,     17,  17,  17,  17, 
            0,   0,   0,   0,      0,   0,   0,   0,      0,   0,   0,   0,      0,   0,   0,   0
        };

    #endif

    extern const int CHAR_WIDTH = 8;
    extern const int CHAR_HEIGHT = 8;
    extern const int NUM_MESSAGES = 3;
    extern const char MESSAGE_0[] PROGMEM = "Happy Halloween! ";
    extern const char MESSAGE_1[] PROGMEM = "Spooktacular! ";
    extern const char MESSAGE_2[] PROGMEM = "^._.^ ";
    extern const char* const MESSAGES[] PROGMEM = {
        MESSAGE_0,
        MESSAGE_1,
        MESSAGE_2,
    };

    // https://github.com/dhepper/font8x8
    // Every character in the font is encoded row-wise in 8 bytes.

    // The least significant bit of each byte corresponds to the first pixel in a
    //  row. 

    // The character 'A' (0x41 / 65) is encoded as 
    // { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}


    //     0x0C => 0000 1100 => ..XX....
    //     0X1E => 0001 1110 => .XXXX...
    //     0x33 => 0011 0011 => XX..XX..
    //     0x33 => 0011 0011 => XX..XX..
    //     0x3F => 0011 1111 => xxxxxx..
    //     0x33 => 0011 0011 => XX..XX..
    //     0x33 => 0011 0011 => XX..XX..
    //     0x00 => 0000 0000 => ........

    // To access the nth pixel in a row, right-shift by n.

    //                          . . X X . . . .
    //                          | | | | | | | |
    //     (0x0C >> 0) & 1 == 0-+ | | | | | | |
    //     (0x0C >> 1) & 1 == 0---+ | | | | | |
    //     (0x0C >> 2) & 1 == 1-----+ | | | | |
    //     (0x0C >> 3) & 1 == 1-------+ | | | |
    //     (0x0C >> 4) & 1 == 0---------+ | | |
    //     (0x0C >> 5) & 1 == 0-----------+ | |
    //     (0x0C >> 6) & 1 == 0-------------+ |
    //     (0x0C >> 7) & 1 == 0---------------+



    extern const byte ASCII_CHARS[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0020 (space)
        0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00,   // U+0021 (!)
        0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0022 (")
        0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00,   // U+0023 (#)
        0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00,   // U+0024 ($)
        0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00,   // U+0025 (%)
        0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00,   // U+0026 (&)
        0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0027 (')
        0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00,   // U+0028 (()
        0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00,   // U+0029 ())
        0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00,   // U+002A (*)
        0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00,   // U+002B (+)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06,   // U+002C (,)
        0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00,   // U+002D (-)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00,   // U+002E (.)
        0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00,   // U+002F (/)
        0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00,   // U+0030 (0)
        0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00,   // U+0031 (1)
        0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00,   // U+0032 (2)
        0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00,   // U+0033 (3)
        0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00,   // U+0034 (4)
        0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00,   // U+0035 (5)
        0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00,   // U+0036 (6)
        0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00,   // U+0037 (7)
        0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00,   // U+0038 (8)
        0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00,   // U+0039 (9)
        0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00,   // U+003A (:)
        0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06,   // U+003B (//)
        0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00,   // U+003C (<)
        0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00,   // U+003D (=)
        0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00,   // U+003E (>)
        0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00,   // U+003F (?)
        0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00,   // U+0040 (@)
        0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00,   // U+0041 (A)
        0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00,   // U+0042 (B)
        0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00,   // U+0043 (C)
        0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00,   // U+0044 (D)
        0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00,   // U+0045 (E)
        0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00,   // U+0046 (F)
        0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00,   // U+0047 (G)
        0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00,   // U+0048 (H)
        0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+0049 (I)
        0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00,   // U+004A (J)
        0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00,   // U+004B (K)
        0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00,   // U+004C (L)
        0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00,   // U+004D (M)
        0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00,   // U+004E (N)
        0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00,   // U+004F (O)
        0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00,   // U+0050 (P)
        0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00,   // U+0051 (Q)
        0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00,   // U+0052 (R)
        0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00,   // U+0053 (S)
        0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+0054 (T)
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00,   // U+0055 (U)
        0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00,   // U+0056 (V)
        0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00,   // U+0057 (W)
        0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00,   // U+0058 (X)
        0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00,   // U+0059 (Y)
        0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00,   // U+005A (Z)
        0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00,   // U+005B ([)
        0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00,   // U+005C (\)
        0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00,   // U+005D (])
        0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00,   // U+005E (^)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,   // U+005F (_)
        0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0060 (`)
        0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00,   // U+0061 (a)
        0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00,   // U+0062 (b)
        0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00,   // U+0063 (c)
        0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00,   // U+0064 (d)
        0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00,   // U+0065 (e)
        0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00,   // U+0066 (f)
        0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F,   // U+0067 (g)
        0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00,   // U+0068 (h)
        0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+0069 (i)
        0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E,   // U+006A (j)
        0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00,   // U+006B (k)
        0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+006C (l)
        0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00,   // U+006D (m)
        0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00,   // U+006E (n)
        0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,   // U+006F (o)
        0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F,   // U+0070 (p)
        0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78,   // U+0071 (q)
        0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00,   // U+0072 (r)
        0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00,   // U+0073 (s)
        0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00,   // U+0074 (t)
        0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00,   // U+0075 (u)
        0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00,   // U+0076 (v)
        0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00,   // U+0077 (w)
        0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00,   // U+0078 (x)
        0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F,   // U+0079 (y)
        0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00,   // U+007A (z)
        0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00,   // U+007B ({)
        0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,   // U+007C (|)
        0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00,   // U+007D (})
        0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // U+007E (~)
    };
}
