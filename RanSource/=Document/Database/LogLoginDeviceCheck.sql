USE [RanUser]
GO

/****** Object:  Table [dbo].[LogLoginDeviceCheck]    Script Date: 11/8/2020 1:08:45 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[LogLoginDeviceCheck](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[PrevPCIDHWID] [varchar](65) NOT NULL,
	[PrevPCIDMAC] [varchar](65) NOT NULL,
	[PrevIP] [varchar](50) NOT NULL,
	[NewPCIDHWID] [varchar](65) NOT NULL,
	[NewPCIDMAC] [varchar](65) NOT NULL,
	[NewIP] [varchar](50) NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_LogLoginDeviceCheck] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_UserID]  DEFAULT ('') FOR [UserID]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_PrevPCIDHWID]  DEFAULT ('') FOR [PrevPCIDHWID]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_PrevPCIDMAC]  DEFAULT ('') FOR [PrevPCIDMAC]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_PrevIP]  DEFAULT ('') FOR [PrevIP]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_NewPCIDHWID]  DEFAULT ('') FOR [NewPCIDHWID]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_NewPCIDMAC]  DEFAULT ('') FOR [NewPCIDMAC]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_NewIP]  DEFAULT ('') FOR [NewIP]
GO

ALTER TABLE [dbo].[LogLoginDeviceCheck] ADD  CONSTRAINT [DF_LogLoginDeviceCheck_Date]  DEFAULT (getdate()) FOR [Date]
GO


