USE [RanGame1]
GO

/****** Object:  Table [dbo].[GameNotice]    Script Date: 6/13/2021 5:07:20 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[GameNotice](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[Message] [varchar](1024) NOT NULL,
	[DaySunday] [int] NOT NULL,
	[DayMonday] [int] NOT NULL,
	[DayTuesday] [int] NOT NULL,
	[DayWednesday] [int] NOT NULL,
	[DayThursday] [int] NOT NULL,
	[DayFriday] [int] NOT NULL,
	[DaySaturday] [int] NOT NULL,
	[Type] [int] NOT NULL,
	[Hour] [int] NOT NULL,
	[Minute] [int] NOT NULL,
 CONSTRAINT [PK_GameNotice] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_Table_1_NoticeMessage]  DEFAULT ('') FOR [Message]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DaySunday]  DEFAULT ((0)) FOR [DaySunday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayMonday]  DEFAULT ((0)) FOR [DayMonday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_Table_1_DayTuesDay]  DEFAULT ((0)) FOR [DayTuesday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayWednesday]  DEFAULT ((0)) FOR [DayWednesday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayThursday]  DEFAULT ((0)) FOR [DayThursday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayFriday]  DEFAULT ((0)) FOR [DayFriday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DaySaturday]  DEFAULT ((0)) FOR [DaySaturday]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_Type]  DEFAULT ((0)) FOR [Type]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_Hour]  DEFAULT ((0)) FOR [Hour]
GO

ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_Minute]  DEFAULT ((0)) FOR [Minute]
GO


