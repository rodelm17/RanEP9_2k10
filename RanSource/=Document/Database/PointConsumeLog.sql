USE [RanUser]
GO

/****** Object:  Table [dbo].[PointConsumeLog]    Script Date: 05/03/2022 2:45:19 pm ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[PointConsumeLog](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [bigint] NOT NULL,
	[Type] [bigint] NOT NULL,
	[Consume] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_PointConsumeLog] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[PointConsumeLog] ADD  CONSTRAINT [DF_PointConsumeLog_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO

ALTER TABLE [dbo].[PointConsumeLog] ADD  CONSTRAINT [DF_PointConsumeLog_Type]  DEFAULT ((0)) FOR [Type]
GO

ALTER TABLE [dbo].[PointConsumeLog] ADD  CONSTRAINT [DF_PointConsumeLog_Consume]  DEFAULT ((0)) FOR [Consume]
GO

ALTER TABLE [dbo].[PointConsumeLog] ADD  CONSTRAINT [DF_PointConsumeLog_Date]  DEFAULT (getdate()) FOR [Date]
GO


