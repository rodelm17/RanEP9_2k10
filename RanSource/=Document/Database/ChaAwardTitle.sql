USE [RanGame1]
GO

/****** Object:  Table [dbo].[ChaAwardTitle]    Script Date: 2/13/2021 2:55:24 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[ChaAwardTitle](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[Title] [varchar](100) NOT NULL,
	[Type] [bigint] NOT NULL,
	[Enabled] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_ChaAwardTitle] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Title]  DEFAULT ('') FOR [Title]
GO

ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Type]  DEFAULT ((0)) FOR [Type]
GO

ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Enabled]  DEFAULT ((0)) FOR [Enabled]
GO

ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Date]  DEFAULT (getdate()) FOR [Date]
GO


