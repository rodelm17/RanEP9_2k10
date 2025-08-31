USE [RanUser]
GO

/****** Object:  Table [dbo].[MasterPasswords]    Script Date: 6/19/2020 6:30:06 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[MasterPasswords](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[MasterPass] [varchar](20) NOT NULL,
 CONSTRAINT [PK_MasterPasswords] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[MasterPasswords] ADD  CONSTRAINT [DF_MasterPasswords_MasterPass]  DEFAULT ('') FOR [MasterPass]
GO


