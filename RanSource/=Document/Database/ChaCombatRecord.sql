USE [RanGame]
GO

/****** Object:  Table [dbo].[ChaCombatRecord]    Script Date: 13/05/2022 1:10:49 pm ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[ChaCombatRecord](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[SGNum] [bigint] NOT NULL,
	[CreatedDate] [datetime] NOT NULL,
	[PVPKills] [bigint] NOT NULL,
	[PVPDeaths] [bigint] NOT NULL,
	[PVPResu] [bigint] NOT NULL,
	[TyrannyKills] [bigint] NOT NULL,
	[TyrannyDeaths] [bigint] NOT NULL,
	[TyrannyResu] [bigint] NOT NULL,
	[ClubWarKills] [bigint] NOT NULL,
	[ClubWarDeaths] [bigint] NOT NULL,
	[ClubWarResu] [bigint] NOT NULL,
	[CaptureTheFlagKills] [bigint] NOT NULL,
	[CaptureTheFlagDeaths] [bigint] NOT NULL,
	[CaptureTheFlagResu] [bigint] NOT NULL,
	[SchoolWarsKills] [bigint] NOT NULL,
	[SchoolWarsDeaths] [bigint] NOT NULL,
	[SchoolWarsResu] [bigint] NOT NULL,
	[ClubDeathMatchKills] [bigint] NOT NULL,
	[ClubDeathMatchDeaths] [bigint] NOT NULL,
	[ClubDeathMatchResu] [bigint] NOT NULL,
	[PKMapKills] [bigint] NOT NULL,
	[PKMapDeaths] [bigint] NOT NULL,
	[PKMapResu] [bigint] NOT NULL,
	[PVEKills] [bigint] NOT NULL,
	[PVEDeaths] [bigint] NOT NULL,
	[PVEMoneyGain] [money] NOT NULL,
 CONSTRAINT [PK_ChaCombatRecord] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CreatedDate]  DEFAULT (getdate()) FOR [CreatedDate]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVPKills]  DEFAULT ((0)) FOR [PVPKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVPDeaths]  DEFAULT ((0)) FOR [PVPDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVPResu]  DEFAULT ((0)) FOR [PVPResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_TyrannyKills]  DEFAULT ((0)) FOR [TyrannyKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_TyrannyDeaths]  DEFAULT ((0)) FOR [TyrannyDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_TyrannyResu]  DEFAULT ((0)) FOR [TyrannyResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubWarKills]  DEFAULT ((0)) FOR [ClubWarKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubWarDeaths]  DEFAULT ((0)) FOR [ClubWarDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubWarResu]  DEFAULT ((0)) FOR [ClubWarResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CaptureTheFlagKills]  DEFAULT ((0)) FOR [CaptureTheFlagKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CaptureTheFlagDeaths]  DEFAULT ((0)) FOR [CaptureTheFlagDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CaptureTheFlagResu]  DEFAULT ((0)) FOR [CaptureTheFlagResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SchoolWarsKills]  DEFAULT ((0)) FOR [SchoolWarsKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SchoolWarsDeaths]  DEFAULT ((0)) FOR [SchoolWarsDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SchoolWarsResu]  DEFAULT ((0)) FOR [SchoolWarsResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubDeathMatchKills]  DEFAULT ((0)) FOR [ClubDeathMatchKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubDeathMatchDeaths]  DEFAULT ((0)) FOR [ClubDeathMatchDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubDeathMatchResu]  DEFAULT ((0)) FOR [ClubDeathMatchResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PKMapKills]  DEFAULT ((0)) FOR [PKMapKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PKMapDeaths]  DEFAULT ((0)) FOR [PKMapDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PKMapResu]  DEFAULT ((0)) FOR [PKMapResu]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVEKills]  DEFAULT ((0)) FOR [PVEKills]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVEDeaths]  DEFAULT ((0)) FOR [PVEDeaths]
GO

ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVEMoneyGain]  DEFAULT ((0)) FOR [PVEMoneyGain]
GO


