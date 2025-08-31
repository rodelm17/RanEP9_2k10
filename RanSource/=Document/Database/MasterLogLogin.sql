USE [RanUser]
GO

/****** Object:  Table [dbo].[MasterLogLogin]    Script Date: 6/19/2020 6:30:02 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[MasterLogLogin](
	[LoginNum] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[Pass] [varchar](20) NOT NULL,
	[LogDate] [datetime] NULL,
	[LogIpAddress] [varchar](23) NULL,
	[LogHWID] [varchar](65) NULL,
	[LogMAC] [varchar](65) NULL,
 CONSTRAINT [PK_MasterLogLogin] PRIMARY KEY CLUSTERED 
(
	[LoginNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[MasterLogLogin] ADD  CONSTRAINT [DF_MasterLogLogin_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO


