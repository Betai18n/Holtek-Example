/*********************************************************************************************************//**
 * @file    project_template/IP/Example/ht32f175x_275x_usbdconf.h
 * @version V1.00
 * @date    07/05/2011
 * @brief   The configuration file of USB Device Driver.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2011 Holtek Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/
// <<< Use Configuration Wizard in Context Menu >>>
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F175X_275X_USBDCONF_H
#define __HT32F175X_275X_USBDCONF_H


/*----------------------------------------------------------------------------------------------------------*/
/* USB Interrupt Enable                                                                                     */
/*----------------------------------------------------------------------------------------------------------*/
//  <h> USB Interrupt Setting (UIER)
//    <o0.0> USB Global Interrupt Enable (UGIE) (Default)
//    <o0.1> Start Of Frame Interrupt Enable (SOFIE)
//    <o0.2> USB Reset Interrupt Enable (URSTIE) (Default)
//    <o0.3> Resume Interrupt Enable (RSMIE) (Default)
//    <o0.4> Suspend Interrupt Enable (SUSPIE) (Default)
//    <o0.5> Expected Start of Frame Interrupt Enable (ESOFE)
//    <o0.8> Control Endpoint Interrupt Enable (EP0IE) (Default)
//    <o0.9> Endpoint1 Interrupt Enable (EP1IE)
//    <o0.10> Endpoint2 Interrupt Enable (EP2IE)
//    <o0.11> Endpoint3 Interrupt Enable (EP3IE)
//    <o0.12> Endpoint4 Interrupt Enable (EP4IE)
//    <o0.13> Endpoint5 Interrupt Enable (EP5IE)
//    <o0.14> Endpoint6 Interrupt Enable (EP6IE)
//    <o0.15> Endpoint7 Interrupt Enable (EP7IE)
#define _UIER               (0x011D)
//  </h>


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint0 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <h> Control Endpoint0 Configuration
//    <o0> Endpoint Buffer Length (EPLEN)
//      <8=> 8 bytes
//      <16=> 16 bytes
//      <32=> 32 bytes
//      <64=> 64 bytes
                            /* Maximum: 64 Bytes                                                            */
#define _EP0LEN             (0x40)


//    <h> Control Endpoint0 Interrupt Enable Settings (EP0IER)
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE) (Default)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE) (Default)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
//      <o0.8> SETUP Token Packet Received Interrupt Enable (STRXIE)
//      <o0.9> SETUP Data Packet Received Interrupt Enable (SDRXIE) (Default)
//      <o0.10> SETUP Data Error Interrupt Enable (SDERIE)
//      <o0.11> Zero Length Data Packet Received Interrupt Enable (ZLRXIE)
#define _EP0_IER            (0x212)
//    </h>
//  </h>

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint1 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint1 Configuration
#define _EP1_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP1_CFG_EPADR      (1)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP1_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <2=> Bulk
//      <3=> Interrupt
#define _EP1_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP1_CFG_EPDIR      (1)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-64:4>
                            /* Maximum: 64 Bytes                                                            */
#define _EP1LEN_TMP         (0x08)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP1_IER            (0x10)
// </h>
// </e>


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint2 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint2 Configuration
#define _EP2_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP2_CFG_EPADR      (2)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP2_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <2=> Bulk
//      <3=> Interrupt
#define _EP2_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP2_CFG_EPDIR      (0)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-64:4>
                            /* Maximum: 64 Bytes                                                            */
#define _EP2LEN_TMP         (0x08)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP2_IER            (0x002)
// </h>
// </e>

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint3 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint3 Configuration
#define _EP3_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP3_CFG_EPADR      (3)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP3_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <2=> Bulk
//      <3=> Interrupt
#define _EP3_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP3_CFG_EPDIR      (1)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-64:4>
                            /* Maximum: 64 Bytes                                                            */
#define _EP3LEN_TMP         (0x08)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP3_IER            (0x10)
// </h>
// </e>

/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint4 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint4 Configuration
#define _EP4_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP4_CFG_EPADR      (4)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP4_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <1=> Isochronous
//      <2=> Bulk
//      <3=> Interrupt
#define _EP4_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP4_CFG_EPDIR      (0)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-500:4>
                            /* Maximum: 500 Bytes                                                           */
#define _EP4LEN_TMP         (0x08)

//    <o0> Single/Double Buffer Selection (SDBS)
//      <0=> Single Buffer
//      <1=> Double Buffer
#define _EP4_CFG_SDBS       (0)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP4_IER            (0x02)
// </h>
// </e>


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint5 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint5 Configuration
#define _EP5_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP5_CFG_EPADR      (5)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP5_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <1=> Isochronous
//      <2=> Bulk
//      <3=> Interrupt
#define _EP5_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP5_CFG_EPDIR      (1)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-500:4>
#define _EP5LEN_TMP         (0x008)
                            /* Maximum: 500 Bytes                                                           */

//    <o0> Single/Double Buffer Selection (SDBS)
//      <0=> Single Buffer
//      <1=> Double Buffer
#define _EP5_CFG_SDBS       (0)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP5_IER            (0x10)
// </h>
// </e>


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint6 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint6 Configuration
#define _EP6_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP6_CFG_EPADR      (6)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP6_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <1=> Isochronous
//      <2=> Bulk
//      <3=> Interrupt
#define _EP6_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP6_CFG_EPDIR      (0)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-500:4>
                            /* Maximum: 500 Bytes                                                           */
#define _EP6LEN_TMP         (0x08)

//    <o0> Single/Double Buffer Selection (SDBS)
//      <0=> Single Buffer
//      <1=> Double Buffer
#define _EP6_CFG_SDBS       (0)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP6_IER            (0x02)
// </h>
// </e>


/*----------------------------------------------------------------------------------------------------------*/
/* Endpoint7 Configuration Setting                                                                          */
/*----------------------------------------------------------------------------------------------------------*/
//  <e0> Endpoint7 Configuration
#define _EP7_ENABLE         (0)

//    <o0> Endpoint Address (EPADR)
//      <1=> 1
//      <2=> 2
//      <3=> 3
//      <4=> 4
//      <5=> 5
//      <6=> 6
//      <7=> 7
#define _EP7_CFG_EPADR      (7)

//    <o0.0> Endpoint Enable (EPEN)
#define _EP7_CFG_EPEN_TMP   (1)

//    <o0> Endpoint Transfer Type
//      <1=> Isochronous
//      <2=> Bulk
//      <3=> Interrupt
#define _EP7_TYPR           (3)

//    <o0> Endpoint Direction (EPDIR)
//      <1=> IN
//      <0=> OUT
#define _EP7_CFG_EPDIR      (1)

//    <o0> Endpoint Buffer Length (EPLEN) (in byte) <4-500:4>
                            /* Maximum: 500 Bytes                                                           */
#define _EP7LEN_TMP         (0x08)

//    <o0> Single/Double Buffer Selection (SDBS)
//      <0=> Single Buffer
//      <1=> Double Buffer
#define _EP7_CFG_SDBS       (0)

//    <h> Endpoint Interrupt Enable Settings (EPIER)
//      <o0> Endpoint Interrupt Enable Settings (EPIER) <0x0-0xFF:1>
//      <o0.0> OUT Token Packet Received Interrupt Enable (OTRXIE)
//      <o0.1> OUT Data Packet Received Interrupt Enable (ODRXIE)
//      <o0.2> OUT Data Buffer Overrun Interrupt Enable (ODOVIE)
//      <o0.3> IN Token Packet Received Interrupt Enable (ITRXIE)
//      <o0.4> IN Data Packet Transmitted Interrupt Enable (IDTXIE)
//      <o0.5> NAK Transmitted Interrupt Enable (NAKIE)
//      <o0.6> STALL Transmitted Interrupt Enable (STLIE)
//      <o0.7> USB Error Interrupt Enable (UERIE)
#define _EP7_IER            (0x10)
// </h>
// </e>

#include "ht32f175x_275x_usbdinit.h"

#endif /* __HT32F175X_275X_USBDCONF_H ----------------------------------------------------------------------*/
