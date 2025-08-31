USE [RanLog]
GO

/****** Object:  Table [dbo].[LogPutOnDrop]    Script Date: 7/7/2019 5:38:22 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[LogPutOnDrop](
	[Num] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[ChaName] [varchar](33) NOT NULL,
	[Serial] [varchar](50) NOT NULL,
	[ItemM] [bigint] NOT NULL,
	[ItemS] [bigint] NOT NULL,
	[ItemGen] [bigint] NOT NULL,
	[MapM] [bigint] NOT NULL,
	[MapS] [bigint] NOT NULL,
	[FactAM] [bigint] NOT NULL,
	[FactAS] [bigint] NOT NULL,
	[FactBM] [bigint] NOT NULL,
	[FactBS] [bigint] NOT NULL,
	[UsePet] [bigint] NOT NULL,
	[PetSkillAM] [bigint] NOT NULL,
	[PetSkillAS] [bigint] NOT NULL,
	[PetSkillBM] [bigint] NOT NULL,
	[PetSkillBS] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_LogPutOnDrop_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_LogPutOnDrop_ChaName]  DEFAULT ('') FOR [ChaName]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_LogPutOnDrop_Serial]  DEFAULT ('') FOR [Serial]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_ItemMain]  DEFAULT ((0)) FOR [ItemM]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_ItemSub]  DEFAULT ((0)) FOR [ItemS]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_LogPutOnDrop_ItemGen]  DEFAULT ((0)) FOR [ItemGen]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_MapMID]  DEFAULT ((0)) FOR [MapM]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_MapSID]  DEFAULT ((0)) FOR [MapS]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_FactAMID]  DEFAULT ((0)) FOR [FactAM]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_FactBMID]  DEFAULT ((0)) FOR [FactBM]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_FactBSID]  DEFAULT ((0)) FOR [FactBS]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_LogPutOnDrop_UsePet]  DEFAULT ((0)) FOR [UsePet]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_PetSkillAMain]  DEFAULT ((0)) FOR [PetSkillAM]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_PetSkillASub]  DEFAULT ((0)) FOR [PetSkillAS]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_PetSkillBMain]  DEFAULT ((0)) FOR [PetSkillBM]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_Table_1_PetSkillBSub]  DEFAULT ((0)) FOR [PetSkillBS]
GO

ALTER TABLE [dbo].[LogPutOnDrop] ADD  CONSTRAINT [DF_LogPutOnDrop_Data]  DEFAULT (getdate()) FOR [Date]
GO


