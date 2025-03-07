#include <stdio.h>  // getchar
#include <stdint.h> // uint8_t...
#include <stdbool.h>
#include <string.h> // memset
#include <ctype.h>  // isprint

#define STRINGIFY(x) #x
#define MAKE_ID_AND_LABEL(name) .id = name, .label = STRINGIFY(name)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define LABEL_MAX_SIZE 8
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
}lbl_id_t;

typedef enum
{
    UNIT_Wh,
    UNIT_W,
    UNIT_A,
    UNIT_V,
    UNIT_VA,
    UNIT_kVA,
    UNIT_Without
}unit_t;

typedef struct
{
    lbl_id_t id;
    char    *label;
    bool     timestamp;
    uint8_t  size;
    unit_t   unit;
}cmd_t;

/* from ENEDIS Enedis-NOI-CPT_54E document
 * only generic commands
 */
cmd_t commands[] = {
    { MAKE_ID_AND_LABEL(ADSC   ), .timestamp = false, .size = 12, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(VTIC   ), .timestamp = false, .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DATE   ), .timestamp = true , .size =  0, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(NGTF   ), .timestamp = false, .size = 16, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(LTARF  ), .timestamp = false, .size = 16, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(EAST   ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF01 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF02 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF03 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF04 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF05 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF06 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF07 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF08 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF09 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASF10 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD01 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD02 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD03 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(EASD04 ), .timestamp = false, .size =  9, .unit = UNIT_Wh      },
    { MAKE_ID_AND_LABEL(IRMS1  ), .timestamp = false, .size =  3, .unit = UNIT_V       },
    { MAKE_ID_AND_LABEL(URMS1  ), .timestamp = false, .size =  3, .unit = UNIT_V       },
    { MAKE_ID_AND_LABEL(PREF   ), .timestamp = false, .size =  2, .unit = UNIT_kVA     },
    { MAKE_ID_AND_LABEL(PCOUP  ), .timestamp = false, .size =  2, .unit = UNIT_kVA     },
    { MAKE_ID_AND_LABEL(SINSTS ), .timestamp = false, .size =  5, .unit = UNIT_VA      },
    { MAKE_ID_AND_LABEL(SINSTS ), .timestamp = false, .size =  5, .unit = UNIT_VA      },
    { MAKE_ID_AND_LABEL(SMAXSN ), .timestamp = true , .size =  5, .unit = UNIT_VA      },
    { SMAXSN_MINUS_1,"SMAXSN-1" , .timestamp = true , .size =  2, .unit = UNIT_VA      },
    { MAKE_ID_AND_LABEL(CCASN  ), .timestamp = true , .size =  5, .unit = UNIT_W       },
    { CCASN_MINUS_1, "CCASN-1"  , .timestamp = true , .size =  5, .unit = UNIT_W       },
    { MAKE_ID_AND_LABEL(UMOY1  ), .timestamp = true , .size =  3, .unit = UNIT_V       },
    { MAKE_ID_AND_LABEL(STGE   ), .timestamp = false, .size =  8, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DPM1   ), .timestamp = true , .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(FPM1   ), .timestamp = true , .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DPM2   ), .timestamp = true , .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(FPM2   ), .timestamp = true , .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(DPM3   ), .timestamp = true , .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(FPM3   ), .timestamp = true , .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(MSG1   ), .timestamp = false, .size = 32, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(MSG2   ), .timestamp = false, .size = 16, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(PRM    ), .timestamp = false, .size = 14, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(RELAIS ), .timestamp = false, .size =  3, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(NTARF  ), .timestamp = false, .size =  2, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(NJOURF ), .timestamp = false, .size =  2, .unit = UNIT_Without },
    { NJOURF_PLUS_1, "NJOURF+1" , .timestamp = false, .size =  2, .unit = UNIT_Without },
    { PJOURF_PLUS_1, "PJOURF+1" , .timestamp = false, .size = 98, .unit = UNIT_Without },
    { MAKE_ID_AND_LABEL(PPOINTE), .timestamp = false, .size = 98, .unit = UNIT_Without },
};

void     state_init  (uint8_t c);
void     state_label (uint8_t c);
lbl_id_t str2label_id(uint8_t *str);

typedef enum {
    STATE_INIT,
    STATE_LABEL,
} state_t;

state_t  state = STATE_INIT;
lbl_id_t current_label = -1;

void (*state_functions[])(uint8_t) = {
    state_init,
    state_label
};

int main(int argc, char* argv[])
{
    int c;
    while ((c = getchar()) != EOF) {
        state_functions[state](c);
    }

    return 0;
}



void state_init(uint8_t c)
{
    if(c == 0x0A)
    {
        state = STATE_LABEL;
    }
}

void state_label(uint8_t c)
{
    static uint8_t idx = 0;
    static uint8_t label_str[LABEL_MAX_SIZE+1];

    /* init at start of new label */
    if(idx == 0)
    {
        memset(label_str, 0, sizeof(label_str));
    }
    
    /* end of label? */
    if(c == 0x09)
    {
        str2label_id(label_str);
        // TODO check if label is correct.
    }

    /* label is too long? */
    if(idx > LABEL_MAX_SIZE)
    {
        state = STATE_INIT;
        printf("Error label is tool long\n");
        idx = 0;
        return;
    }

    /* valid caracter ? */
    if(!isprint(c))
    {
        state = STATE_INIT;
        idx = 0;
        return;
    }

    label_str[idx++] = c;
}

lbl_id_t str2label_id(uint8_t *str)
{
    for(uint8_t i = 0; i < ARRAY_SIZE(commands); i++)
    {
        if(!strcmp((const char *)str, commands[i].label))
        {
            printf("found id %s\n", str);
            return commands[i].id;
        }
    }

    /* id not found */
    printf("id not found %s\n", str);
    return -1;
}