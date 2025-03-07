#include <stdint.h> // uint8_t...
#include <stdbool.h>

#define STRINGIFY(x) #x
#define MAKE_ID_AND_LABEL(name) .id = name, .label = STRINGIFY(name)

typedef enum
{
    ADSC,
    VTIC,
    DATE,
    NGTF,
    LTARF,
    EAST,
    EASF01,
    EASF02,
    EASF03,
    EASF04,
    EASF05,
    EASF06,
    EASF07,
    EASF08,
    EASF09,
    EASF10,
    EASD01,
    EASD02,
    EASD03,
    EASD04,
    IRMS1,
    URMS1,
    PREF,
    PCOUP,
    SINSTS,
    SMAXSN,
    SMAXSN_MINUS_1,
    CCASN,
    CCASN_MINUS_1,
    UMOY1,
    STGE,
    DPM1,
    FPM1,
    DPM2,
    FPM2,
    DPM3,
    FPM3,
    MSG1,
    MSG2,
    PRM,
    RELAIS,
    NTARF,
    NJOURF,
    NJOURF_PLUS_1,
    PJOURF_PLUS_1,
    PPOINTE
}e_cmd_id;

typedef enum
{
    UNIT_Wh,
    UNIT_W,
    UNIT_A,
    UNIT_V,
    UNIT_VA,
    UNIT_kVA,
    UNIT_Without
}e_unit;

typedef struct
{
    e_cmd_id id;
    char    *label;
    bool     have_timestamp;
    uint8_t  data_size;
    e_unit   unit;
}cmd_t;

/* from ENEDIS Enedis-NOI-CPT_54E document
 * only generic commands, no specific
 */
cmd_t commands[] = {
    { MAKE_ID_AND_LABEL(ADSC   ), .have_timestamp = false, .data_size = 12, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(VTIC   ), .have_timestamp = false, .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DATE   ), .have_timestamp = true , .data_size =  0, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(NGTF   ), .have_timestamp = false, .data_size = 16, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(LTARF  ), .have_timestamp = false, .data_size = 16, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(EAST   ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF01 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF02 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF03 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF04 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF05 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF06 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF07 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF08 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF09 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF10 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD01 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD02 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD03 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD04 ), .have_timestamp = false, .data_size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(IRMS1  ), .have_timestamp = false, .data_size =  3, .unit = UNIT_V       },
    { MAKE_ID_AND_LABEL(URMS1  ), .have_timestamp = false, .data_size =  3, .unit = UNIT_V       },
    { MAKE_ID_AND_LABEL(PREF   ), .have_timestamp = false, .data_size =  2, .unit = UNIT_kVA     },
    { MAKE_ID_AND_LABEL(PCOUP  ), .have_timestamp = false, .data_size =  2, .unit = UNIT_kVA     },
    { MAKE_ID_AND_LABEL(SINSTS ), .have_timestamp = false, .data_size =  5, .unit = UNIT_VA      },
    { MAKE_ID_AND_LABEL(SINSTS ), .have_timestamp = false, .data_size =  5, .unit = UNIT_VA      },
    { MAKE_ID_AND_LABEL(SMAXSN ), .have_timestamp = true , .data_size =  5, .unit = UNIT_VA      },
    { SMAXSN_MINUS_1,"SMAXSN-1" , .have_timestamp = true , .data_size =  2, .unit = UNIT_VA      },
    { MAKE_ID_AND_LABEL(CCASN  ), .have_timestamp = true , .data_size =  5, .unit = UNIT_W       },
    { CCASN_MINUS_1, "CCASN-1"  , .have_timestamp = true , .data_size =  5, .unit = UNIT_W       },
    { MAKE_ID_AND_LABEL(UMOY1  ), .have_timestamp = true , .data_size =  3, .unit = UNIT_V       },
    { MAKE_ID_AND_LABEL(STGE   ), .have_timestamp = false, .data_size =  8, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DPM1   ), .have_timestamp = true , .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(FPM1   ), .have_timestamp = true , .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DPM2   ), .have_timestamp = true , .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(FPM2   ), .have_timestamp = true , .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DPM3   ), .have_timestamp = true , .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(FPM3   ), .have_timestamp = true , .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(MSG1   ), .have_timestamp = false, .data_size = 32, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(MSG2   ), .have_timestamp = false, .data_size = 16, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(PRM    ), .have_timestamp = false, .data_size = 14, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(RELAIS ), .have_timestamp = false, .data_size =  3, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(NTARF  ), .have_timestamp = false, .data_size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(NJOURF ), .have_timestamp = false, .data_size =  2, .unit = UNIT_Without },
    { NJOURF_PLUS_1, "NJOURF+1" , .have_timestamp = false, .data_size =  2, .unit = UNIT_Without },
    { PJOURF_PLUS_1, "PJOURF+1" , .have_timestamp = false, .data_size = 98, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(PPOINTE), .have_timestamp = false, .data_size = 98, .unit = UNIT_Without },
};

int main(int argc, char* argv[])
{

    return 0;
}
