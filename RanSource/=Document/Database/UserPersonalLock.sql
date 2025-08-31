USE [RanGame1]
GO

/****** Object:  Table [dbo].[UserPersonalLock]    Script Date: 01/15/2020 06:57:03 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[UserPersonalLock](
	[Num] [int] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[SGNum] [int] NOT NULL,
	[UserLockPuton] [bigint] NOT NULL,
	[UserLockInven] [bigint] NOT NULL,
	[UserLockLocker] [bigint] NOT NULL,
	[UserPinPuton] [varchar](4) NOT NULL,
	[UserPinInven] [varchar](4) NOT NULL,
	[UserPinLocker] [varchar](4) NOT NULL,
 CONSTRAINT [PK_UserPersonalLock] PRIMARY KEY CLUSTERED 
(
	[Num] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[UserPersonalLock] ADD  CONSTRAINT [DF_UserPersonalLock_UserLockPuton]  DEFAULT ((0)) FOR [UserLockPuton]
GO

ALTER TABLE [dbo].[UserPersonalLock] ADD  CONSTRAINT [DF_UserPersonalLock_UserLockInven]  DEFAULT ((0)) FOR [UserLockInven]
GO

ALTER TABLE [dbo].[UserPersonalLock] ADD  CONSTRAINT [DF_UserPersonalLock_UserLockLocker]  DEFAULT ((0)) FOR [UserLockLocker]
GO

ALTER TABLE [dbo].[UserPersonalLock] ADD  CONSTRAINT [DF_UserPersonalLock_UserPinPuton]  DEFAULT ('') FOR [UserPinPuton]
GO

ALTER TABLE [dbo].[UserPersonalLock] ADD  CONSTRAINT [DF_UserPersonalLock_UserPinInven]  DEFAULT ('') FOR [UserPinInven]
GO

ALTER TABLE [dbo].[UserPersonalLock] ADD  CONSTRAINT [DF_UserPersonalLock_UserPinLocker]  DEFAULT ('') FOR [UserPinLocker]
GO


