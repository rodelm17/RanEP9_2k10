USE [RanLog]
GO

/****** Object:  Table [dbo].[LogGMParty]    Script Date: 6/13/2021 9:02:35 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[LogGMParty](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[GMUserNum] [bigint] NOT NULL,
	[GMChaNum] [bigint] NOT NULL,
	[GMChaName] [varchar](33) NOT NULL,
	[GMUserType] [bigint] NOT NULL,
	[TargetUserNum] [bigint] NOT NULL,
	[TargetChaNum] [bigint] NOT NULL,
	[TargetChaName] [varchar](33) NOT NULL,
	[TargetUserType] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_LogGMParty] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_UserNum]  DEFAULT ((0)) FOR [GMUserNum]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_GMChaNum]  DEFAULT ((0)) FOR [GMChaNum]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_GMChaName]  DEFAULT ('') FOR [GMChaName]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_GMUserType]  DEFAULT ((0)) FOR [GMUserType]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_TargetUserNum]  DEFAULT ((0)) FOR [TargetUserNum]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_TargetChaNum]  DEFAULT ((0)) FOR [TargetChaNum]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_TargetChaName]  DEFAULT ('') FOR [TargetChaName]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_TargetUserType]  DEFAULT ((0)) FOR [TargetUserType]
GO

ALTER TABLE [dbo].[LogGMParty] ADD  CONSTRAINT [DF_LogGMParty_Date]  DEFAULT (getdate()) FOR [Date]
GO


