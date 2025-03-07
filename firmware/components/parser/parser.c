#include <stdio.h>  // getchar
#include <stdint.h> // uint8_t...
#include <stdbool.h>
#include <string.h> // memset
#include <ctype.h>  // isprint

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define LABEL_MAX_SIZE 8

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
    char    *label;
    bool     timestamp;
    uint8_t  size;
    unit_t   unit;
}cmd_t;

/* from ENEDIS Enedis-NOI-CPT_54E document
 * only generic commands
 */
cmd_t commands[] = {
    /* label, timestamp, size, unit */
    { "ADSC",     false, 12, UNIT_Without },
    { "VTIC",     false,  2, UNIT_Without },
    { "DATE",     true ,  0, UNIT_Without },
    { "NGTF",     false, 16, UNIT_Without },
    { "LTARF",    false, 16, UNIT_Without },
    { "EAST",     false,  9, UNIT_Wh      },
    { "EASF01",   false,  9, UNIT_Wh      },
    { "EASF02",   false,  9, UNIT_Wh      },
    { "EASF03",   false,  9, UNIT_Wh      },
    { "EASF04",   false,  9, UNIT_Wh      },
    { "EASF05",   false,  9, UNIT_Wh      },
    { "EASF06",   false,  9, UNIT_Wh      },
    { "EASF07",   false,  9, UNIT_Wh      },
    { "EASF08",   false,  9, UNIT_Wh      },
    { "EASF09",   false,  9, UNIT_Wh      },
    { "EASF10",   false,  9, UNIT_Wh      },
    { "EASD01",   false,  9, UNIT_Wh      },
    { "EASD02",   false,  9, UNIT_Wh      },
    { "EASD03",   false,  9, UNIT_Wh      },
    { "EASD04",   false,  9, UNIT_Wh      },
    { "IRMS1",    false,  3, UNIT_V       },
    { "URMS1",    false,  3, UNIT_V       },
    { "PREF",     false,  2, UNIT_kVA     },
    { "PCOUP",    false,  2, UNIT_kVA     },
    { "SINSTS",   false,  5, UNIT_VA      },
    { "SINSTS",   false,  5, UNIT_VA      },
    { "SMAXSN",   true ,  5, UNIT_VA      },
    { "SMAXSN-1", true ,  2, UNIT_VA      },
    { "CCASN",    true ,  5, UNIT_W       },
    { "CCASN-1",  true ,  5, UNIT_W       },
    { "UMOY1",    true ,  3, UNIT_V       },
    { "STGE",     false,  8, UNIT_Without },
    { "DPM1",     true ,  2, UNIT_Without },
    { "FPM1",     true ,  2, UNIT_Without },
    { "DPM2",     true ,  2, UNIT_Without },
    { "FPM2",     true ,  2, UNIT_Without },
    { "DPM3",     true ,  2, UNIT_Without },
    { "FPM3",     true ,  2, UNIT_Without },
    { "MSG1",     false, 32, UNIT_Without },
    { "MSG2",     false, 16, UNIT_Without },
    { "PRM",      false, 14, UNIT_Without },
    { "RELAIS",   false,  3, UNIT_Without },
    { "NTARF",    false,  2, UNIT_Without },
    { "NJOURF",   false,  2, UNIT_Without },
    { "NJOURF+1", false,  2, UNIT_Without },
    { "PJOURF+1", false, 98, UNIT_Without },
    { "PPOINTE",  false, 98, UNIT_Without },
};

void     state_init     (uint8_t c);
void     state_label    (uint8_t c);
void     state_timestamp(uint8_t c);
void     state_data     (uint8_t c);

uint8_t str2label_id(uint8_t *str);

typedef enum {
    STATE_INIT,
    STATE_LABEL,
    STATE_TIMESTAMP,
    STATE_DATA
} state_t;

state_t  state = STATE_INIT;
uint8_t current_label = -1;

void (*state_functions[])(uint8_t) = {
    state_init,
    state_label,
    state_timestamp,
    state_data
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
        current_label = str2label_id(label_str);
        if(commands[current_label].timestamp)
        {
            state = STATE_TIMESTAMP;
        } else {
            state = STATE_DATA;
        }
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

uint8_t str2label_id(uint8_t *str)
{
    for(uint8_t i = 0; i < ARRAY_SIZE(commands); i++)
    {
        if(!strcmp((const char *)str, commands[i].label))
        {
            printf("found id %s\n", str);
            return i;
        }
    }

    /* id not found */
    printf("id not found %s\n", str);
    return -1;
}

void     state_timestamp(uint8_t c)
{

}

void     state_data     (uint8_t c)
{

}