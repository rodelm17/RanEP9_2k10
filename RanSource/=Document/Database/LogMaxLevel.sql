USE [RanLog]
GO

/****** Object:  Table [dbo].[LogMaxLevel]    Script Date: 7/26/2021 6:01:04 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[LogMaxLevel](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [bigint] NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[ChaName] [varchar](33) NOT NULL,
	[ChaLevel] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_LogMaxLevel] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[LogMaxLevel] ADD  CONSTRAINT [DF_LogMaxLevel_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO

ALTER TABLE [dbo].[LogMaxLevel] ADD  CONSTRAINT [DF_LogMaxLevel_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[LogMaxLevel] ADD  CONSTRAINT [DF_LogMaxLevel_ChaName]  DEFAULT ('') FOR [ChaName]
GO

ALTER TABLE [dbo].[LogMaxLevel] ADD  CONSTRAINT [DF_LogMaxLevel_ChaLevel]  DEFAULT ((0)) FOR [ChaLevel]
GO

ALTER TABLE [dbo].[LogMaxLevel] ADD  CONSTRAINT [DF_LogMaxLevel_Date]  DEFAULT (getdate()) FOR [Date]
GO


