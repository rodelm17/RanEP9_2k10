USE [RanUser]
GO

/****** Object:  Table [dbo].[LogLogin]    Script Date: 4/15/2020 8:55:16 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[LogLogin](
	[LoginNum] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[LogInOut] [int] NOT NULL,
	[LogDate] [datetime] NULL,
	[LogIpAddress] [varchar](23) NULL,
	[LogHWID] [varchar](65) NULL,
	[LogMAC] [varchar](65) NULL,
 CONSTRAINT [PK_LogLogin] PRIMARY KEY CLUSTERED 
(
	[LoginNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[LogLogin] ADD  CONSTRAINT [DF_LogLogin_LogInOut]  DEFAULT ((0)) FOR [LogInOut]
GO

ALTER TABLE [dbo].[LogLogin] ADD  CONSTRAINT [DF_LogLogin_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO


