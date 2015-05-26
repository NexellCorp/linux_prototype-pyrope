//------------------------------------------------------------------------------
//
//	Copyright (C) Nexell Co. 2012
//
//  This confidential and proprietary software may be used only as authorized by a
//  licensing agreement from Nexell Co.
//  The entire notice above must be reproduced on all authorized copies and copies
//  may only be made to the extent permitted by a licensing agreement from Nexell Co.
//
//	Module		:
//	File		: nx_MPEGTSI.c
//	Description	:
//	Author		: Sei (parkjh@nexell.co.kr)
//	History		:
//------------------------------------------------------------------------------
#include <nx_chip.h>
#include "nx_mpegtsi.h"

static struct
{
    struct NX_MPEGTSI_RegisterSet * pRegister;
} __g_ModuleVariables = {CNULL, };

//------------------------------------------------------------------------------
// Module Interface
//------------------------------------------------------------------------------
CBOOL	NX_MPEGTSI_Initialize( void )
{
	static CBOOL bInit = CFALSE;

	if( CFALSE == bInit )
	{
		__g_ModuleVariables.pRegister = CNULL;
		bInit = CTRUE;
	}

	return CTRUE;
}

U32     NX_MPEGTSI_GetNumberOfModule( void )
{
    return  NUMBER_OF_MPEGTSI_MODULE;
}

//------------------------------------------------------------------------------
// Basic Interface
//------------------------------------------------------------------------------
U32		NX_MPEGTSI_GetPhysicalAddress( void )
{
	return  (U32)PHY_BASEADDR_MPEGTSI_MODULE;
}

U32		NX_MPEGTSI_GetSizeOfRegisterSet( void )
{
	return sizeof( struct NX_MPEGTSI_RegisterSet );
}


void	NX_MPEGTSI_SetBaseAddress( void* BaseAddress )
{
	NX_ASSERT( CNULL != BaseAddress );

	__g_ModuleVariables.pRegister = (struct NX_MPEGTSI_RegisterSet *) BaseAddress;
}


void*	NX_MPEGTSI_GetBaseAddress( void )
{

	return (void*)__g_ModuleVariables.pRegister;
}

CBOOL	NX_MPEGTSI_OpenModule( void )
{
    NX_ASSERT( __g_ModuleVariables.pRegister != CNULL );
	return CTRUE;
}

CBOOL	NX_MPEGTSI_CloseModule( void )
{
    NX_ASSERT( __g_ModuleVariables.pRegister != CNULL );
	return CTRUE;
}

CBOOL	NX_MPEGTSI_CheckBusy( void )
{
	return CFALSE;
}

CBOOL	NX_MPEGTSI_CanPowerDown( void )
{
	return CTRUE;
}

//------------------------------------------------------------------------------
// Colck & Reset Control
//------------------------------------------------------------------------------
U32     NX_MPEGTSI_GetClockNumber( void )
{
    static const U32 CLKGEN_MPEGTSI_LIST[] =
    {
        CLOCKINDEX_LIST( MPEGTSI )
    };

    return (U32)CLKGEN_MPEGTSI_LIST[0];
}

U32     NX_MPEGTSI_GetResetNumber( void )
{
    const U32 RSTCON_MPEGTSI_LIST[] =
    {
        RESETINDEX_LIST( MPEGTSI, i_nRST )
    };

    return (U32)RSTCON_MPEGTSI_LIST[0];
}

//------------------------------------------------------------------------------
// Interrupt Interface
//------------------------------------------------------------------------------
S32     NX_MPEGTSI_GetInterruptNumber( void )
{
    const U32   MPEGTSI_IntNumList[NUMBER_OF_MPEGTSI_MODULE] = { INTNUM_LIST( MPEGTSI ) };

    NX_ASSERT( MPEGTSI_IntNumList != CNULL );

    return  MPEGTSI_IntNumList[0];
}

//------------------------------------------------------------------------------
// DMA Interface
//------------------------------------------------------------------------------
U32     NX_MPEGTSI_GetDMAIndex( U32 ChannelIndex )
{
    const U32 MPEGTSI_DMANumber[4] = {
        DMAINDEX_WITH_CHANNEL_LIST(MPEGTSI, MPTSIDMA0),
        DMAINDEX_WITH_CHANNEL_LIST(MPEGTSI, MPTSIDMA1),
        DMAINDEX_WITH_CHANNEL_LIST(MPEGTSI, MPTSIDMA2),
        DMAINDEX_WITH_CHANNEL_LIST(MPEGTSI, MPTSIDMA3)
    };

    NX_ASSERT( ChannelIndex < 4 );

    return MPEGTSI_DMANumber[ChannelIndex];
}

U32     NX_MPEGTSI_GetDMABusWidth( void )
{
    return 32;
}

void    NX_MPEGTSI_SetIDMAEnable( U32 ChannelIndex, CBOOL Enable )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    IDMA_MASK = 1UL << ChannelIndex;

    RegVal  = pRegister->IDMAEN;
    RegVal &= ~IDMA_MASK;
    RegVal |= Enable << ChannelIndex;

    WriteIO32( &pRegister->IDMAEN, RegVal );
}

U32     NX_MPEGTSI_GetIDMAEnable( void )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    return (U32)__g_ModuleVariables.pRegister->IDMAEN;
}

void    NX_MPEGTSI_RunIDMA( U32 ChannelIndex )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    IDMA_MASK = 1UL << ChannelIndex;

    WriteIO32( &pRegister->IDMARUN, IDMA_MASK );
}

void    NX_MPEGTSI_StopIDMA( U32 ChannelIndex )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    IDMA_MASK = 1UL << (ChannelIndex+16);

    WriteIO32( &pRegister->IDMARUN, IDMA_MASK );
}

void    NX_MPEGTSI_SetIDMABaseAddr( U32 ChannelIndex, U32 BaseAddr )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    WriteIO32( &pRegister->IDMAADDR[ChannelIndex], BaseAddr );
}

U32     NX_MPEGTSI_GetIDMABaseAddr( U32 ChannelIndex )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    return (U32)__g_ModuleVariables.pRegister->IDMAADDR[ChannelIndex];
}

void    NX_MPEGTSI_SetIDMALength( U32 ChannelIndex, U32 Length )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    WriteIO32( &pRegister->IDMALEN[ChannelIndex], Length );
}

U32     NX_MPEGTSI_GetIDMALength( U32 ChannelIndex )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    return (U32)__g_ModuleVariables.pRegister->IDMALEN[ChannelIndex];
}

void    NX_MPEGTSI_SetIDMAIntEnable( U32 ChannelIndex, CBOOL Enable )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    IDMA_MASK = 1UL << (ChannelIndex+16);

    RegVal  = pRegister->IDMAINT;
    RegVal &= ~IDMA_MASK;
    RegVal |= Enable << (ChannelIndex+16);

    WriteIO32( &pRegister->IDMAINT, RegVal );
}

U32     NX_MPEGTSI_GetIDMAIntEnable( void )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (U32)(((__g_ModuleVariables.pRegister->IDMAINT)>>16) & 0xF);
}

void    NX_MPEGTSI_SetIDMAIntMask( U32 ChannelIndex, CBOOL Enable )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    IDMA_MASK = 1UL << (ChannelIndex+24);

    RegVal  = pRegister->IDMAINT;
    RegVal &= ~IDMA_MASK;
    RegVal |= Enable << (ChannelIndex+24);

    WriteIO32( &pRegister->IDMAINT, RegVal );
}

U32     NX_MPEGTSI_GetIDMAIntMask( void )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (U32)(((__g_ModuleVariables.pRegister->IDMAINT)>>24) & 0xF);
}

CBOOL   NX_MPEGTSI_GetIDMAIntPending( U32 ChannelIndex )
{
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );

    IDMA_MASK = 1UL << (ChannelIndex+8);

    return (CBOOL)((__g_ModuleVariables.pRegister->IDMAINT & IDMA_MASK)>>(ChannelIndex+8));
}

void    NX_MPEGTSI_ClearIDMAIntPending( U32 ChannelIndex )
{
    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;
    U32 IDMA_MASK;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( ChannelIndex <= 3 );     // 4ch

    pRegister   = __g_ModuleVariables.pRegister;

    IDMA_MASK = 1UL << (ChannelIndex);

    RegVal  = pRegister->IDMAINT;
    RegVal &= ~IDMA_MASK;
    RegVal |= 1UL << (ChannelIndex);

    WriteIO32( &pRegister->IDMAINT, RegVal );
}

//------------------------------------------------------------------------------
// Module Function Interface
//------------------------------------------------------------------------------
void    NX_MPEGTSI_SetCapEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   CAPENB_POS  = 0;
    const U32   CAPENB_MASK = 1UL << CAPENB_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~CAPENB_MASK;
    RegVal |= Enable << CAPENB_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetCapEnable( U32 CapIdx )
{
    const U32   CAPENB_POS  = 0;
    const U32   CAPENB_MASK = 1UL << CAPENB_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & CAPENB_MASK) >> CAPENB_POS);
}

void    NX_MPEGTSI_SetSerialEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   SERIAL_POS  = 1;
    const U32   SERIAL_MASK = 1UL << SERIAL_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~SERIAL_MASK;
    RegVal |= Enable << SERIAL_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetSerialEnable( U32 CapIdx )
{
    const U32   SERIAL_POS  = 1;
    const U32   SERIAL_MASK = 1UL << SERIAL_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & SERIAL_MASK) >> SERIAL_POS);
}

void    NX_MPEGTSI_SetTCLKPolarityEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   CLKPOL_POS  = 4;
    const U32   CLKPOL_MASK = 1UL << CLKPOL_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~CLKPOL_MASK;
    RegVal |= Enable << CLKPOL_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetTCLKPolarityEnable( U32 CapIdx )
{
    const U32   CLKPOL_POS  = 4;
    const U32   CLKPOL_MASK = 1UL << CLKPOL_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & CLKPOL_MASK) >> CLKPOL_POS);
}

void    NX_MPEGTSI_SetTDPPolarityEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   TDPPOL_POS  = 5;
    const U32   TDPPOL_MASK = 1UL << TDPPOL_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~TDPPOL_MASK;
    RegVal |= Enable << TDPPOL_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetTDPPolarityEnable( U32 CapIdx )
{
    const U32   TDPPOL_POS  = 5;
    const U32   TDPPOL_MASK = 1UL << TDPPOL_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & TDPPOL_MASK) >> TDPPOL_POS);
}

void    NX_MPEGTSI_SetTSYNCPolarityEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   SYNPOL_POS  = 6;
    const U32   SYNPOL_MASK = 1UL << SYNPOL_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~SYNPOL_MASK;
    RegVal |= Enable << SYNPOL_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetTSYNCPolarityEnable( U32 CapIdx )
{
    const U32   SYNPOL_POS  = 6;
    const U32   SYNPOL_MASK = 1UL << SYNPOL_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & SYNPOL_MASK) >> SYNPOL_POS);
}

void    NX_MPEGTSI_SetTERRPolarityEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   ERRPOL_POS  = 7;
    const U32   ERRPOL_MASK = 1UL << ERRPOL_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~ERRPOL_MASK;
    RegVal |= Enable << ERRPOL_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetTERRPolarityEnable( U32 CapIdx )
{
    const U32   ERRPOL_POS  = 7;
    const U32   ERRPOL_MASK = 1UL << ERRPOL_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & ERRPOL_MASK) >> ERRPOL_POS);
}

void    NX_MPEGTSI_SetCapSramSleepEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   CAPSLP_POS  = 8;
    const U32   CAPSLP_MASK = 1UL << CAPSLP_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~CAPSLP_MASK;
    RegVal |= (!Enable) << CAPSLP_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetCapSramSleepEnable( U32 CapIdx )
{
    const U32   CAPSLP_POS  = 8;
    const U32   CAPSLP_MASK = 1UL << CAPSLP_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)(!((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & CAPSLP_MASK) >> CAPSLP_POS));
}

void    NX_MPEGTSI_SetCapSramPowerEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   CAPPOW_POS  = 9;
    const U32   CAPPOW_MASK = 1UL << CAPPOW_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~CAPPOW_MASK;
    RegVal |= Enable << CAPPOW_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetCapSramPowerEnable( U32 CapIdx )
{
    const U32   CAPPOW_POS  = 9;
    const U32   CAPPOW_MASK = 1UL << CAPPOW_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & CAPPOW_MASK) >> CAPPOW_POS);
}

void    NX_MPEGTSI_SetCap1OutputEnable( CBOOL Enable )
{
    const U32   OUTENB_POS  = 16;
    const U32   OUTENB_MASK = 1UL << OUTENB_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[1];
    RegVal &= ~OUTENB_MASK;
    RegVal |= Enable << OUTENB_POS;

    WriteIO32( &pRegister->CAP_CTRL[1], RegVal );
}

CBOOL   NX_MPEGTSI_GetCap1OutputEnable( void )
{
    const U32   OUTENB_POS  = 16;
    const U32   OUTENB_MASK = 1UL << OUTENB_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[1] & OUTENB_MASK) >> OUTENB_POS);
}

void    NX_MPEGTSI_SetCap1OutTCLKPolarityEnable( CBOOL Enable )
{
    const U32   OUTPOL_POS  = 17;
    const U32   OUTPOL_MASK = 1UL << OUTPOL_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[1];
    RegVal &= ~OUTPOL_MASK;
    RegVal |= Enable << OUTPOL_POS;

    WriteIO32( &pRegister->CAP_CTRL[1], RegVal );
}

CBOOL   NX_MPEGTSI_GetCap1OutPolarityEnable( void )
{
    const U32   OUTPOL_POS  = 17;
    const U32   OUTPOL_MASK = 1UL << OUTPOL_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[1] & OUTPOL_MASK) >> OUTPOL_POS);
}

void    NX_MPEGTSI_SetCapIntLockEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   INTLOCK_POS  = 24;
    const U32   INTLOCK_MASK = 1UL << INTLOCK_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~INTLOCK_MASK;
    RegVal |= Enable << INTLOCK_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetCapIntLockEnable( U32 CapIdx )
{
    const U32   INTLOCK_POS  = 24;
    const U32   INTLOCK_MASK = 1UL << INTLOCK_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & INTLOCK_MASK) >> INTLOCK_POS);
}

void    NX_MPEGTSI_SetCapIntEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   CAPINT_POS  = 25;
    const U32   CAPINT_MASK = 1UL << CAPINT_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~CAPINT_MASK;
    RegVal |= Enable << CAPINT_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetCapIntEnable( U32 CapIdx )
{
    const U32   CAPINT_POS  = 25;
    const U32   CAPINT_MASK = 1UL << CAPINT_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & CAPINT_MASK) >> CAPINT_POS);
}

void    NX_MPEGTSI_SetCapIntMaskEnable( U32 CapIdx, CBOOL Enable )
{
    const U32   CAPMASK_POS  = 26;
    const U32   CAPMASK_MASK = 1UL << CAPMASK_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CAP_CTRL[CapIdx];
    RegVal &= ~CAPMASK_MASK;
    RegVal |= Enable << CAPMASK_POS;

    WriteIO32( &pRegister->CAP_CTRL[CapIdx], RegVal );
}

CBOOL   NX_MPEGTSI_GetCapIntMaskEnable( U32 CapIdx )
{
    const U32   CAPMASK_POS  = 26;
    const U32   CAPMASK_MASK = 1UL << CAPMASK_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)((__g_ModuleVariables.pRegister->CAP_CTRL[CapIdx] & CAPMASK_MASK) >> CAPMASK_POS);
}

void    NX_MPEGTSI_SetCPUWrData( U32 WrData )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    WriteIO32( &__g_ModuleVariables.pRegister->CPU_WRDATA, WrData );
}

void    NX_MPEGTSI_SetCPUWrAddr( U32 WrAddr )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    WriteIO32( &__g_ModuleVariables.pRegister->CPU_WRADDR, WrAddr );
}

void    NX_MPEGTSI_SetTsiRun( CBOOL Enable )
{
    const U32   TSIRUN_POS  = 0;
    const U32   TSIRUN_MASK = 1UL << TSIRUN_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CTRL0;
    RegVal &= ~TSIRUN_MASK;
    RegVal |= Enable << TSIRUN_POS;

    WriteIO32( &pRegister->CTRL0, RegVal );
}

CBOOL   NX_MPEGTSI_GetTsiRun( void )
{
    const U32   TSIRUN_POS  = 0;
    const U32   TSIRUN_MASK = 1UL << TSIRUN_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CTRL0 & TSIRUN_MASK) >> TSIRUN_POS);
}

void    NX_MPEGTSI_SetTsiEncrypt( CBOOL Enable )
{
    const U32   TSIENC_POS  = 1;
    const U32   TSIENC_MASK = 1UL << TSIENC_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CTRL0;
    RegVal &= ~TSIENC_MASK;
    RegVal |= Enable << TSIENC_POS;

    WriteIO32( &pRegister->CTRL0, RegVal );
}

CBOOL   NX_MPEGTSI_GetTsiEncrypt( void )
{
    const U32   TSIENC_POS  = 1;
    const U32   TSIENC_MASK = 1UL << TSIENC_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CTRL0 & TSIENC_MASK) >> TSIENC_POS);
}

void    NX_MPEGTSI_SetTsiSramSleepEnable( CBOOL Enable )
{
    const U32   TSISLP_POS  = 6;
    const U32   TSISLP_MASK = 1UL << TSISLP_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CTRL0;
    RegVal &= ~TSISLP_MASK;
    RegVal |= (!Enable) << TSISLP_POS;

    WriteIO32( &pRegister->CTRL0, RegVal );
}

CBOOL   NX_MPEGTSI_GetTsiSramSleepEnable( void )
{
    const U32   TSISLP_POS  = 6;
    const U32   TSISLP_MASK = 1UL << TSISLP_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)(!((__g_ModuleVariables.pRegister->CTRL0 & TSISLP_MASK) >> TSISLP_POS));
}

void    NX_MPEGTSI_SetTsiSramPowerEnable( CBOOL Enable )
{
    const U32   TSIPOW_POS  = 7;
    const U32   TSIPOW_MASK = 1UL << TSIPOW_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CTRL0;
    RegVal &= ~TSIPOW_MASK;
    RegVal |= Enable << TSIPOW_POS;

    WriteIO32( &pRegister->CTRL0, RegVal );
}

CBOOL   NX_MPEGTSI_GetTsiSramPowerEnable( void )
{
    const U32   TSIPOW_POS  = 7;
    const U32   TSIPOW_MASK = 1UL << TSIPOW_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CTRL0 & TSIPOW_MASK) >> TSIPOW_POS);
}

void    NX_MPEGTSI_SetTsiIntEnable( CBOOL Enable )
{
    const U32   TSIINT_POS  = 16;
    const U32   TSIINT_MASK = 1UL << TSIINT_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CTRL0;
    RegVal &= ~TSIINT_MASK;
    RegVal |= Enable << TSIINT_POS;

    WriteIO32( &pRegister->CTRL0, RegVal );
}

CBOOL   NX_MPEGTSI_GetTsiIntEnable( void )
{
    const U32   TSIINT_POS  = 16;
    const U32   TSIINT_MASK = 1UL << TSIINT_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CTRL0 & TSIINT_MASK) >> TSIINT_POS);
}

void    NX_MPEGTSI_SetTsiIntMaskEnable( CBOOL Enable )
{
    const U32   TSIMASK_POS  = 17;
    const U32   TSIMASK_MASK = 1UL << TSIMASK_POS;

    register struct NX_MPEGTSI_RegisterSet * pRegister;
    register U32    RegVal;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( (CTRUE==Enable) || (CFALSE==Enable) );

    pRegister   = __g_ModuleVariables.pRegister;

    RegVal  = pRegister->CTRL0;
    RegVal &= ~TSIMASK_MASK;
    RegVal |= Enable << TSIMASK_POS;

    WriteIO32( &pRegister->CTRL0, RegVal );
}

CBOOL   NX_MPEGTSI_GetTsiMaskIntEnable( void )
{
    const U32   TSIMASK_POS  = 17;
    const U32   TSIMASK_MASK = 1UL << TSIMASK_POS;

    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)((__g_ModuleVariables.pRegister->CTRL0 & TSIMASK_MASK) >> TSIMASK_POS);
}

U32     NX_MPEGTSI_GetCapData( U32 CapIdx )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );
    NX_ASSERT( CapIdx < 2 );

    return (CBOOL)(__g_ModuleVariables.pRegister->CAP_DATA[CapIdx]);
}

U32     NX_MPEGTSI_GetTsiOutData( void )
{
    NX_ASSERT( CNULL != __g_ModuleVariables.pRegister );

    return (CBOOL)(__g_ModuleVariables.pRegister->TSP_OUTDATA);
}

