USE [RanGame1]
GO

/****** Object:  Table [dbo].[ChaPKCombo]    Script Date: 2/13/2021 5:36:29 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[ChaPKCombo](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[SGNum] [bigint] NOT NULL,
	[CreatedDate] [datetime] NOT NULL,
	[PKCombo00] [bigint] NOT NULL,
	[PKCombo01] [bigint] NOT NULL,
	[PKCombo02] [bigint] NOT NULL,
	[PKCombo03] [bigint] NOT NULL,
	[PKCombo04] [bigint] NOT NULL,
	[PKCombo05] [bigint] NOT NULL,
	[PKCombo06] [bigint] NOT NULL,
	[PKCombo07] [bigint] NOT NULL,
 CONSTRAINT [PK_ChaPKCombo] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_CreatedDate]  DEFAULT (getdate()) FOR [CreatedDate]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo00]  DEFAULT ((0)) FOR [PKCombo00]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo01]  DEFAULT ((0)) FOR [PKCombo01]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo02]  DEFAULT ((0)) FOR [PKCombo02]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo03]  DEFAULT ((0)) FOR [PKCombo03]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo04]  DEFAULT ((0)) FOR [PKCombo04]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo05]  DEFAULT ((0)) FOR [PKCombo05]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo06]  DEFAULT ((0)) FOR [PKCombo06]
GO

ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo07]  DEFAULT ((0)) FOR [PKCombo07]
GO


