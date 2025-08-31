USE [RanUser]
GO

/****** Object:  Table [dbo].[UserKey]    Script Date: 4/15/2020 8:48:06 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[UserKey](
	[Num] [int] IDENTITY(1,1) NOT NULL,
	[PCIDHWID] [varchar](65) NOT NULL,
	[PCIDMAC] [varchar](65) NOT NULL,
	[PCIDUserNum] [bigint] NOT NULL,
	[PCIDUserID] [varchar](33) NOT NULL,
	[PCIDSGNum] [bigint] NOT NULL,
	[PCIDDate] [datetime] NOT NULL
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDHWID]  DEFAULT ('') FOR [PCIDHWID]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDMAC]  DEFAULT ('') FOR [PCIDMAC]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDUserNum]  DEFAULT ((0)) FOR [PCIDUserNum]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDUserID]  DEFAULT ('') FOR [PCIDUserID]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDSGNum]  DEFAULT ((0)) FOR [PCIDSGNum]
GO

ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDDate]  DEFAULT (getdate()) FOR [PCIDDate]
GO


