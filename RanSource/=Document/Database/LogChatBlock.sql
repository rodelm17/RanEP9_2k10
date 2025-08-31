USE [RanUser]
GO

/****** Object:  Table [dbo].[LogChatBlock]    Script Date: 9/24/2020 11:03:27 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[LogChatBlock](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [bigint] NOT NULL,
	[UserID] [varchar](33) NOT NULL,
	[ChatBlockDate] [datetime] NOT NULL,
	[ChatBlockReason] [varchar](512) NOT NULL,
	[GMUserNum] [bigint] NOT NULL,
	[GMUserID] [varchar](33) NOT NULL,
 CONSTRAINT [PK_LogChatBlock] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO

ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_UserID]  DEFAULT ('') FOR [UserID]
GO

ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_ChatBlockDate]  DEFAULT ('1970-02-01') FOR [ChatBlockDate]
GO

ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_ChatBlockReason]  DEFAULT ('') FOR [ChatBlockReason]
GO

ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_GMUserNum]  DEFAULT ((0)) FOR [GMUserNum]
GO

ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_GMUserID]  DEFAULT ('') FOR [GMUserID]
GO


