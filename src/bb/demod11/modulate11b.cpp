#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include "const.h"
#include "CRC32.h"
#include "soratime.h"
#include "bb/bbb.h"
#include "bb/DataRate.h"
#include "dot11_pkt.h"
#include "atx.h"
#include "bb_test.h"

extern TIMESTAMPINFO tsinfo;

UCHAR temp[] = 
{
0x00,0xF9,0x00,0xC0,0x00,0xB1,0x00,0xC0,0x00,0xCB,0x00,0xC0,0x00,0xB1,0x00,0xC0,

0x00,0xFA,0x00,0x3F,0x00,0x5E,0x00,0x3F,0x00,0xFA,0x00,0xC0,0x00,0xB1,0x00,0xC0,

0x00,0xCB,0x00,0xC0,0x00,0xB7,0x00,0xC0,0x00,0xCB,0x00,0xC0,0xFF,0xAE,0x00,0xC0,

0x00,0x00,0x00,0x3F,0x00,0x50,0x00,0x3F,0x00,0x34,0x00,0x3F,0xFE,0x48,0x00,0x3F,

0x02,0x36,0x00,0x3F,0xFB,0x4A,0x00,0x3F,0x19,0x1D,0x3F,0x00,0x54,0xF9,0x3F,0x00,

0x03,0x03,0xC0,0x00,0xA2,0xFD,0xC0,0x00,0x04,0x01,0x3F,0x00,0x4F,0xFF,0x3F,0x00,

0x33,0x00,0x3F,0x00,0x4F,0xFF,0x3F,0x00,0x05,0x00,0xC0,0x00,0xA1,0x00,0xC0,0x00,

0x05,0x00,0x3F,0x00,0x4E,0x00,0x3F,0x00,0x34,0x00,0x3F,0x00,0x48,0x00,0x3F,0x00,

0x34,0x00,0x3F,0x00,0x50,0x00,0x3F,0x00,0x00,0x00,0xC0,0x00,0xAF,0x00,0xC0,0x00,

0xCC,0x00,0xC0,0x00,0xB6,0x00,0xC0,0x00,0xCC,0x00,0xC0,0x00,0xB0,0x00,0xC0,0x00,

0xFC,0x00,0x3F,0x00,0x5B,0x00,0x3F,0x00,0x00,0x00,0xC0,0x00,0xA5,0x00,0xC0,0x00,

0x02,0x00,0x3F,0x00,0x50,0x00,0x3F,0x00,0x32,0x00,0x3F,0x00,0x4F,0x00,0x3F,0x00,

0x04,0x00,0xC0,0x00,0xA1,0x00,0xC0,0x00,0x05,0x00,0x3F,0x00,0x4E,0x00,0x3F,0x00,

0x34,0x00,0x3F,0x00,0x48,0x00,0x3F,0x00,0x34,0xFF,0x3F,0x00,0x51,0x00,0x3F,0x00,

0x00,0x00,0xC0,0x00,0xAF,0x00,0xC0,0x00,0xCB,0xFF,0xC0,0x00,0xB7,0x01,0xC0,0x00,

0xC9,0xFD,0xC0,0x00,0xB5,0x04,0xC0,0x00,0xE2,0xE6,0x00,0xC0,0x06,0xAB,0x00,0xC0,

0xFC,0xFC,0x00,0x3F,0x02,0x5D,0x00,0x3F,0xFE,0xFB,0x00,0xC0,0x00,0xB0,0x00,0xC0,

0xFF,0xCC,0x00,0xC0,0x00,0xB0,0x00,0xC0,0xFF,0xFA,0x00,0x3F,0x00,0x5E,0x00,0x3F,

0x00,0xFA,0x00,0xC0,0x00,0xB1,0x00,0xC0,0x00,0xCB,0x00,0xC0,0x00,0xB7,0x00,0xC0,

0x00,0xCB,0x00,0xC0,0x00,0xAE,0x00,0xC0,0x00,0x00,0x00,0x3F,0x00,0x50,0x00,0x3F,

0x00,0x34,0x00,0x3F,0x00,0x48,0x00,0x3F,0x00,0x36,0x00,0x3F,0x00,0x4A,0x00,0x3F,

0x00,0x1D,0x00,0x00,0x00,0xF9,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0xFD,0x00,0x00,

0x00,0x01,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

#define MAX_PHY_ACK_SIZE      16 * 1024
static A16 COMPLEX8 TempAckIntermidiateOutput[MAX_PHY_ACK_SIZE];

void Save(PUCHAR buf, ULONG size)
{
    ULONG i;
#pragma warning (push)
#pragma warning (disable:4996)
    FILE *file = fopen("d:\\fir_input.txt", "w");
#pragma warning (pop)
    
    for (i = 0; i < size; i++)
    {
        fprintf(file, "%3d\n", buf[i]);
    }
    fclose(file);
}

ULONG TestModAck(PUCHAR PhyACKBuffer)
{
    int i;
    ULONG crc32;
    DOT11_MAC_ACK_FRAME  AckFrame       = {0};
    DOT11B_PLCP_TXVECTOR Dot11BTxVector = {0};
    UINT OutputLength = 0;
    ULONG OutputLengthFIR = 0;
    MAC_ADDRESS RecvMacAddress;

    RecvMacAddress.Address[0] = 0x00;
    RecvMacAddress.Address[1] = 0x14;
    RecvMacAddress.Address[2] = 0x6c;
    RecvMacAddress.Address[3] = 0xe2;
    RecvMacAddress.Address[4] = 0x00;
    RecvMacAddress.Address[5] = 0xe5;
    AckFrame.FrameControl.Subtype   = SUBT_ACK;
    AckFrame.FrameControl.Type      = FRAME_CTRL;
    AckFrame.RecvAddress            = RecvMacAddress;
    AckFrame.Duration               = 0;
    AckFrame.FCS                    = CalcCRC32((PUCHAR)&AckFrame, sizeof(DOT11_MAC_ACK_FRAME) - sizeof(ULONG));

    Dot11BTxVector.PreambleType         = DOT11B_PLCP_IS_SHORT_PREAMBLE;
    Dot11BTxVector.DateRate             = DOT11B_PLCP_DATA_RATE_2M;
    Dot11BTxVector.ModSelect            = DOT11B_PLCP_IS_CCK;

    BB11BPMDBufferTx4XWithShortHeader(
        &Dot11BTxVector, 
        (PUCHAR)&AckFrame, 
        sizeof(DOT11_MAC_ACK_FRAME) - 4,
        (PUCHAR)TempAckIntermidiateOutput, &OutputLength); //OutputLength is COMPLEX8 count
    crc32 = CalcCRC32((PUCHAR)TempAckIntermidiateOutput, OutputLength * sizeof(COMPLEX8));
    //printf("inter crc32=0x%08x\n", crc32);
    if (crc32 != 0xaca87240)
    {
        printf("crc32 for FIR input is different, 0x%08x", crc32);
    }
    memset(((PUCHAR)TempAckIntermidiateOutput) + OutputLength * sizeof(COMPLEX8), 
        0x00, 64);
    Save((PUCHAR)TempAckIntermidiateOutput, OutputLength * sizeof(COMPLEX8));
    BB11BPMDSpreadFIR4SSE(
        TempAckIntermidiateOutput, 
        OutputLength, 
        (PCOMPLEX8)PhyACKBuffer, &OutputLengthFIR);
    for (i = 0; i < 512; i++)
    {
        if (temp[i] != PhyACKBuffer[OutputLength * sizeof(COMPLEX8) - 512 + i])
        {
            printf("bug exists\n");
            printf("%d\n", PhyACKBuffer[OutputLength * sizeof(COMPLEX8) - 512 + i]);
            break;
        }
    }
    crc32 = CalcCRC32((PUCHAR)PhyACKBuffer, OutputLength * sizeof(COMPLEX8));
    //printf("out crc32=0x%08x\n", crc32);
    
    if (crc32 != 0xfdf0c0fc)
    {
        printf("crc32 for FIR input is different, 0x%08x\n", crc32);
    }
    else
    {
        Save((PUCHAR)PhyACKBuffer, OutputLength * sizeof(COMPLEX8));
    }
    ASSERT(OutputLength == OutputLengthFIR);
    return OutputLength * sizeof(COMPLEX8);
    
}
void CompareACK()
{
    PUCHAR PhyACKBuffer1 = (PUCHAR)malloc(MAX_PHY_ACK_SIZE);
    PUCHAR PhyACKBuffer1Align = (PUCHAR)((ULONG)(PhyACKBuffer1 + 16) & 0xFFFFFFF0);
    ULONG Len1;
    memset(PhyACKBuffer1, 0xcd, MAX_PHY_ACK_SIZE);

    Len1 = TestModAck(PhyACKBuffer1Align);
    
    free(PhyACKBuffer1);
}


// Note: defined as static variables to prevent TestMod11B() stack too large
const int SAMPLE_BUFFER_SIZE = 2*1024*1024;
static UCHAR               DataBuffer[INPUT_MAX];
static A16 COMPLEX8        TempBuffer[SAMPLE_BUFFER_SIZE];
static A16 COMPLEX8        SymbolBuffer[SAMPLE_BUFFER_SIZE];

int TestMod11B(PDOT11_MOD_ARGS pArgs)
{
    MDL                                 Mdl;
    PACKET_BASE                         Packet;
    DOT11B_PLCP_TXVECTOR                Dot11BTxVector;
    Dot11BTxVector.PreambleType         = DOT11B_PLCP_IS_LONG_PREAMBLE;
    Dot11BTxVector.ModSelect            = DOT11B_PLCP_IS_CCK;

    if (!Dot11BRate_KbpsValid(pArgs->nBitRate))
    {
        printf("Data rate %d kbps is not supported by 802.11b mode\n", pArgs->nBitRate);
        return -1;
    }
    Dot11BTxVector.DateRate = Dot11BDataRate_Kbps2Code(pArgs->nBitRate);

    // Measure modulation speed
    const int RUN_TIMES = 100;
	ULONGLONG ts1 = SoraGetCPUTimestamp ( &tsinfo );
    for (int ii = 0; ii < RUN_TIMES; ii++)
    {
        if (PreparePacket(pArgs->pcInFileName, &Mdl, &Packet, DataBuffer, (PUCHAR)SymbolBuffer, SAMPLE_BUFFER_SIZE) < 0)
            return -1;
        // Note: BB11BPMDPacketGenSignal() will modify Packet.pMdl and Packet.pReserved (data crc)
        //   so if run multiple times, please reload these data before calling it.
        BB11BPMDPacketGenSignal(&Packet, &Dot11BTxVector, (PUCHAR)TempBuffer, sizeof(TempBuffer)/sizeof(COMPLEX8));
    }
	ULONGLONG ts2 = SoraGetCPUTimestamp ( &tsinfo );

    printf("Signal data rate:    %d kbps\n", Dot11BDataRate_Code2Kbps(Dot11BTxVector.DateRate));
    printf("Signal packet size:  %d\n", Packet.PacketSize);
    printf("Signal encoded size: %d\n", Packet.Reserved3);
    printf("Time cost average:   %.3f us \n", SoraTimeElapsed (ts2-ts1, &tsinfo) * 1.0 / 1000 / RUN_TIMES);

    FILE* pOut = NULL;
#pragma warning (push)
#pragma warning (disable:4996)
    pOut = fopen(pArgs->pcOutFileName, "w+b");
#pragma warning (pop)
    if (!pOut)
    {
        printf("Cannot create output file.\n");
        return -1;
    }

    fwrite(Packet.pReserved, Packet.Reserved3, 1, pOut);
    fclose(pOut);

    return 0;
}