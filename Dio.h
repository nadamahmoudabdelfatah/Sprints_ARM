#ifndef DIO_H
#define DIO_H

#include "Std_types.h"
#include "Dio_Cfg.h"
#define Dio_ChannelType         uint8
#define Dio_PortType            uint8
#define Dio_LevelType           uint8
#define Dio_PortLevelType       uint8

typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;
typedef struct
{
	/* Member contains the ID of the Port that this channel belongs to */
	Dio_PortType Port_Num;
}Dio_ConfigChannel;



void Dio_Init(const Dio_ConfigChannel * ConfigPtr);
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);






#endif