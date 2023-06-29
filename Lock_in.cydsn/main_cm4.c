#include "project.h"
#include "arm_math.h"
#include "arm_const_structs.h"

#include <stdio.h>
#include <math.h>

//----------------------------------------------------------------------------------------------------

typedef enum{
    CARRIER_SIGNALS,
    DETECTED_SIGNAL,
    REFERENCE_SIGNALS,
    MIXED_SIGNALS,
    DEMODULATED_SIGNALS,
    FILTERED_SIGNALS,
    INTEREST_SIGNALS
}signal_en_t;

//----------------------------------------------------------------------------------------------------

/*Constantes e variáveis para as funções de filtragem do CMSIS DSP*/

#define IIR_ORDER 4U
#define NUM_STAGES (IIR_ORDER/2)

//----------------------------------------------------------------------------------------------------

//*Filtro passa-baixas de segunda ordem e fc = 10 [Hz] quando a taxa de amostragem for 2 [kHz]
static float32_t lpf11State[IIR_ORDER/2];
static float32_t lpf11Coeffs[5*NUM_STAGES/2] = {
        0.01546629140310334, 0.01546629140310334, 0, 0.9690674171937933, 0// b0, b1, b2, a1, a2
};
arm_biquad_cascade_df2T_instance_f32 const S_lpf11 = {NUM_STAGES/2,lpf11State,lpf11Coeffs};
//*/

//*Filtro passa-baixas de segunda ordem e fc = 10 [Hz] quando a taxa de amostragem for 2 [kHz]
static float32_t lpf12State[IIR_ORDER/2];
static float32_t lpf12Coeffs[5*NUM_STAGES/2] = {
        0.01546629140310334, 0.01546629140310334, 0, 0.9690674171937933, 0// b0, b1, b2, a1, a2
};
arm_biquad_cascade_df2T_instance_f32 const S_lpf12 = {NUM_STAGES/2,lpf12State,lpf12Coeffs};
//*/


//*Filtro passa-baixas de segunda ordem e fc = 10 [Hz] quando a taxa de amostragem for 2 [kHz]
static float32_t lpf21State[IIR_ORDER/2];
static float32_t lpf21Coeffs[5*NUM_STAGES/2] = {
        0.01546629140310334, 0.01546629140310334, 0, 0.9690674171937933, 0// b0, b1, b2, a1, a2
};
arm_biquad_cascade_df2T_instance_f32 const S_lpf21 = {NUM_STAGES/2,lpf21State,lpf21Coeffs};
//*/

//*Filtro passa-baixas de segunda ordem e fc = 10 [Hz] quando a taxa de amostragem for 2 [kHz]
static float32_t lpf22State[IIR_ORDER/2];
static float32_t lpf22Coeffs[5*NUM_STAGES/2] = {
        0.01546629140310334, 0.01546629140310334, 0, 0.9690674171937933, 0// b0, b1, b2, a1, a2
};
arm_biquad_cascade_df2T_instance_f32 const S_lpf22 = {NUM_STAGES/2,lpf22State,lpf22Coeffs};
//*/

//*Filtro passa-altas de quarta ordem e fc = 1 [Hz] quando a taxa de amostragem for 2 [kHz]
static float32_t hpf1State[IIR_ORDER];
static float32_t hpf1Coeffs[5*NUM_STAGES] = {
    0.9959037221384243, -1.9918074442768485, 0.9959037221384243, 1.9942020618642575, -0.9942119028974503,// b0, b1, b2, a1, a2
    1, -2, 1, 1.9975885625502152, -0.9975984202951879// b0, b1, b2, a1, a2
};
arm_biquad_cascade_df2T_instance_f32 const S_hpf1 = {NUM_STAGES,hpf1State,hpf1Coeffs};
//*/

//*Filtro passa-altas de quarta ordem e fc = 1 [Hz] quando a taxa de amostragem for 2 [kHz]
static float32_t hpf2State[IIR_ORDER];
static float32_t hpf2Coeffs[5*NUM_STAGES] = {
    0.9959037221384243, -1.9918074442768485, 0.9959037221384243, 1.9942020618642575, -0.9942119028974503,// b0, b1, b2, a1, a2
    1, -2, 1, 1.9975885625502152, -0.9975984202951879// b0, b1, b2, a1, a2
};
arm_biquad_cascade_df2T_instance_f32 const S_hpf2 = {NUM_STAGES,hpf2State,hpf2Coeffs};
//*/

//----------------------------------------------------------------------------------------------------

/*Constantes e variáveis da medição de frequência cardiaca e oximetria*/

#define BLOCK_SIZE 8

volatile signal_en_t selected_signal;

uint32_t sample_x[BLOCK_SIZE];
uint32_t sample_l740[BLOCK_SIZE];
uint32_t sample_l850[BLOCK_SIZE];

float32_t x[BLOCK_SIZE];
float32_t l740[BLOCK_SIZE];
float32_t l850[BLOCK_SIZE];

float32_t sin1[BLOCK_SIZE] = {0,0.70711,1,0.70711,0,-0.70711,-1,-0.70711};
float32_t cos1[BLOCK_SIZE] = {1,0.70711,0,-0.70711,-1,-0.70711,0,0.70711};
float32_t sin2[BLOCK_SIZE] = {0,1,0,-1,0,1,0,-1};
float32_t cos2[BLOCK_SIZE] = {1,0,-1,0,1,0,-1,0};

float32_t s_11[BLOCK_SIZE];
float32_t s_12[BLOCK_SIZE];
float32_t s_21[BLOCK_SIZE];
float32_t s_22[BLOCK_SIZE];

float32_t u_11[BLOCK_SIZE];
float32_t u_12[BLOCK_SIZE];
float32_t u_21[BLOCK_SIZE];
float32_t u_22[BLOCK_SIZE];

float32_t a_1[BLOCK_SIZE];
float32_t a_2[BLOCK_SIZE];

float32_t y_1[BLOCK_SIZE];
float32_t y_2[BLOCK_SIZE];

//----------------------------------------------------------------------------------------------------

void send_carrier_signals()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f,%f\n",l740[i],l850[i]);
    }
}

void send_detector_signal()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f\n",x[i]);
    }
}

void send_reference_signals()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f,%f,%f,%f\n",sin1[i],cos1[i],sin2[i],cos2[i]);
    }
}

void send_mixed_signals()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f,%f,%f,%f\n",s_11[i],s_12[i],s_21[i],s_22[i]);
    }
}

void send_demodulated_signals()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f,%f,%f,%f\n",u_11[i],u_12[i],u_21[i],u_22[i]);
    }
}

void send_filtered_signals()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f,%f\n",a_1[i],a_2[i]);
    }
}

void send_interest_signals()
{
    for(int i=0; i< BLOCK_SIZE;i++)
    {
        printf("%f,%f\n",y_1[i],y_2[i]);
    }
}

//----------------------------------------------------------------------------------------------------

//Rotina de interrupção do DMA:
void dma_irq_handler()
{ 
    uint8_t i;
    
    //Conversão das amostras para [V]:
    for(i = 0; i < BLOCK_SIZE; i++)
    {
        x[i]=DETECTOR_ADC_CountsTo_Volts(0,sample_x[i]);
        l740[i]=DETECTOR_ADC_CountsTo_Volts(1,sample_l740[i]);
        l850[i]=DETECTOR_ADC_CountsTo_Volts(2,sample_l850[i]);
    }
    
    //Detecção do sinal referente à luz de 740 [nm]:
    for(i = 0; i < BLOCK_SIZE; i++)
    {
        s_11[i]=x[i]*sin1[i];
        s_12[i]=x[i]*cos1[i];
    }    
    arm_biquad_cascade_df2T_f32(&S_lpf11,&s_11[0],&u_11[0],BLOCK_SIZE);
    arm_biquad_cascade_df2T_f32(&S_lpf12,&s_12[0],&u_12[0],BLOCK_SIZE);
    for(i = 0; i < BLOCK_SIZE; i++){
        a_1[i] = (PI/2)*(2*sqrt(u_11[i]*u_11[i]+u_12[i]*u_12[i]));
    }
    arm_biquad_cascade_df2T_f32(&S_hpf1,&a_1[0],&y_1[0],BLOCK_SIZE);
    
    //Detecção do sinal referente à luz de 850 [nm]:
    for(i = 0; i < BLOCK_SIZE; i++)
    {
        s_21[i]=x[i]*sin2[i];
        s_22[i]=x[i]*cos2[i];
    }    
    arm_biquad_cascade_df2T_f32(&S_lpf21,&s_21[0],&u_21[0],BLOCK_SIZE);
    arm_biquad_cascade_df2T_f32(&S_lpf22,&s_22[0],&u_22[0],BLOCK_SIZE);
    for(i = 0; i < BLOCK_SIZE; i++){
        a_2[i] = (PI/2)*(2*sqrt(u_21[i]*u_21[i]+u_22[i]*u_22[i]));
    }
    arm_biquad_cascade_df2T_f32(&S_hpf2,&a_2[0],&y_2[0],BLOCK_SIZE);

    //Transimissão dos sinais selecionados:
    switch(selected_signal)
    {
    case CARRIER_SIGNALS:
        send_carrier_signals();
        break;
    case DETECTED_SIGNAL:
        send_detector_signal();
        break;
    case REFERENCE_SIGNALS:
        send_reference_signals();
        break;
    case MIXED_SIGNALS:
        send_mixed_signals();
        break;
    case DEMODULATED_SIGNALS:
        send_demodulated_signals();
        break;
    case FILTERED_SIGNALS:
        send_filtered_signals();
        break;
    case INTEREST_SIGNALS:
        send_interest_signals();
        break;
    default:
        break;
    };
}

//Rotina de interrupção do UART:
void uart_irq_handler()
{   
    uint8_t value;
    
    Cy_SCB_UART_GetArray(UART_HW, &value, 1); 
    
    switch(value)
    {
    case '0':
        selected_signal = CARRIER_SIGNALS;
        break;
    case '1':
        selected_signal = DETECTED_SIGNAL;
        break;
    case '2':
        selected_signal = REFERENCE_SIGNALS;
        break;
    case '3':
        selected_signal = MIXED_SIGNALS;
        break;
    case '4':
        selected_signal = DEMODULATED_SIGNALS;
        break;
    case '5':
        selected_signal = FILTERED_SIGNALS;
        break;
    case '6':
        selected_signal = INTEREST_SIGNALS;
        break;
    default:
        //Nada a fazer...
        break;
    }
    
    Cy_SCB_UART_ClearRxFifoStatus(UART_HW,CY_SCB_UART_RX_NOT_EMPTY);
}

//Rotina de configuração do DMA:
void configure_dma(void)
{
	cy_en_dma_status_t dma_init_status;
	
    cy_stc_dma_channel_config_t channel_config;	

    //Inicializando os descritores:
    
    dma_init_status = Cy_DMA_Descriptor_Init(&ADC_DMA_Descriptor_1, &ADC_DMA_Descriptor_1_config);    
    dma_init_status = Cy_DMA_Descriptor_Init(&ADC_DMA_Descriptor_2, &ADC_DMA_Descriptor_2_config);
    dma_init_status = Cy_DMA_Descriptor_Init(&ADC_DMA_Descriptor_3, &ADC_DMA_Descriptor_3_config);

    //Initializando o canal de acesso direto à memória:
    
    channel_config.descriptor  = &ADC_DMA_Descriptor_1;
    channel_config.preemptable = ADC_DMA_PREEMPTABLE;
    channel_config.priority    = ADC_DMA_PRIORITY;
    channel_config.enable      = 0u;
  
    dma_init_status = Cy_DMA_Channel_Init(ADC_DMA_HW, ADC_DMA_DW_CHANNEL, &channel_config);
	
    //Definindo os endereços de origem e destino dos descritores:

    Cy_DMA_Descriptor_SetSrcAddress(&ADC_DMA_Descriptor_1, (uint32 *)&(SAR->CHAN_RESULT[0]));
    Cy_DMA_Descriptor_SetDstAddress(&ADC_DMA_Descriptor_1, (uint32_t *) sample_x);
    
    Cy_DMA_Descriptor_SetSrcAddress(&ADC_DMA_Descriptor_2, (uint32 *)&(SAR->CHAN_RESULT[1]));
    Cy_DMA_Descriptor_SetDstAddress(&ADC_DMA_Descriptor_2, (uint32_t *) sample_l740);

    Cy_DMA_Descriptor_SetSrcAddress(&ADC_DMA_Descriptor_3, (uint32 *)&(SAR->CHAN_RESULT[2]));
    Cy_DMA_Descriptor_SetDstAddress(&ADC_DMA_Descriptor_3, (uint32_t *) sample_l850);
           
    //Inicializando o interruptor de acesso direto à memória:
    
    Cy_SysInt_Init(&DMA_INTERRUPT_cfg,&dma_irq_handler);
    NVIC_ClearPendingIRQ(DMA_INTERRUPT_cfg.intrSrc);
	NVIC_EnableIRQ(DMA_INTERRUPT_cfg.intrSrc);
    
    //Habilitando o canal de acesso direto à memória:
    
    Cy_DMA_Channel_Enable(ADC_DMA_HW, ADC_DMA_DW_CHANNEL);
    Cy_DMA_Enable(ADC_DMA_HW);
}


//Função principal:
int main(void)
{         
    //Inicializando as variáveis e estruturas envolvidas no processamento digital dos sinais: 
    
    selected_signal = CARRIER_SIGNALS;
            
    memset(lpf11State, 0, sizeof(lpf11State));
    memset(lpf12State, 0, sizeof(lpf12State));
    memset(lpf21State, 0, sizeof(lpf21State));
    memset(lpf22State, 0, sizeof(lpf22State));
    memset(hpf1State, 0, sizeof(hpf1State));
    memset(hpf2State, 0, sizeof(hpf2State));

    memset(x, 0, sizeof(x));
    memset(l740, 0, sizeof(l740));
    memset(l850, 0, sizeof(l850));  
    
    memset(s_11, 0, sizeof(s_11));
    memset(u_11, 0, sizeof(u_11));
    memset(u_12, 0, sizeof(u_12));
    memset(a_1, 0, sizeof(a_1));
    memset(y_1, 0, sizeof(y_1));

    memset(s_21, 0, sizeof(s_21));
    memset(u_21, 0, sizeof(u_21));
    memset(u_22, 0, sizeof(u_22));
    memset(a_2, 0, sizeof(a_2));
    memset(y_2, 0, sizeof(y_2));
    
    //Configurando o acesso direto à memória:
    
    configure_dma();
    
    //Inicializando o interruptor da FIFO do bloco de comunicação UART:
    
    Cy_SysInt_Init(&UART_INTERRUPT_cfg,&uart_irq_handler);
    NVIC_ClearPendingIRQ(UART_INTERRUPT_cfg.intrSrc);
	NVIC_EnableIRQ(UART_INTERRUPT_cfg.intrSrc);
    
    //Habilitando as interrupções:
    
    __enable_irq();
    
    //Inicializando os componentes periféricos:
    
    UART_Start();
    
    L740_PWM_Start();
    L850_PWM_Start();
    
    DETECTOR_ADC_Start();
    DETECTOR_ADC_StartConvert();
    
    SOC_PWM_Start();    
    
    //Laço de piscagem do LED de estado:
    
    for(;;)
    {
        CyDelay(1000);
        Cy_GPIO_Write(RED_PORT,RED_NUM,0);
        CyDelay(1000);
        Cy_GPIO_Write(RED_PORT,RED_NUM,1);
    }
}