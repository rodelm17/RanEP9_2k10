USE [RanLog]
GO

/****** Object:  Table [dbo].[gm_logs]    Script Date: 08/17/2018 01:22:01 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[gm_logs](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[GMUserID] [bigint] NOT NULL,
	[GMUserType] [bigint] NOT NULL,
	[GMCharID] [bigint] NOT NULL,
	[GMCharName] [varchar](33) NOT NULL,
	[GMCommand] [varchar](1024) NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_gm_logs] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[gm_logs] ADD  CONSTRAINT [DF_gm_logs_Date]  DEFAULT (getdate()) FOR [Date]
GO


