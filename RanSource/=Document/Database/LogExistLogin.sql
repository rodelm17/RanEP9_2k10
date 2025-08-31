USE [RanUser]
GO

/****** Object:  Table [dbo].[LogExistLogin]    Script Date: 12/18/2019 05:52:03 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[LogExistLogin](
	[LogNum] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [bigint] NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[LogIpAddress] [varchar](23) NOT NULL,
	[LogDate] [datetime] NOT NULL,
 CONSTRAINT [PK_LogExistLogin] PRIMARY KEY CLUSTERED 
(
	[LogNum] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO

ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_UserID]  DEFAULT ('') FOR [UserID]
GO

ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_LogIpAddress]  DEFAULT ('') FOR [LogIpAddress]
GO

ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO


