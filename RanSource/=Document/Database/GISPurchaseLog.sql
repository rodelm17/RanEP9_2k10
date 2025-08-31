USE [RanShop]
GO

/****** Object:  Table [dbo].[GISPurchaseLog]    Script Date: 27/12/2021 9:50:32 pm ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[GISPurchaseLog](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ProductNum] [int] NOT NULL,
	[ItemMain] [int] NOT NULL,
	[ItemSub] [int] NOT NULL,
	[ItemMoney] [int] NOT NULL,
	[Date] [datetime] NOT NULL,
	[UserID] [varchar](50) NOT NULL,
 CONSTRAINT [PK_GISPurchaseLog] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[GISPurchaseLog] ADD  CONSTRAINT [DF_GISPurchaseLog_ProductNum]  DEFAULT ((0)) FOR [ProductNum]
GO

ALTER TABLE [dbo].[GISPurchaseLog] ADD  CONSTRAINT [DF_GISPurchaseLog_ItemMain]  DEFAULT ((0)) FOR [ItemMain]
GO

ALTER TABLE [dbo].[GISPurchaseLog] ADD  CONSTRAINT [DF_GISPurchaseLog_ItemSub]  DEFAULT ((0)) FOR [ItemSub]
GO

ALTER TABLE [dbo].[GISPurchaseLog] ADD  CONSTRAINT [DF_GISPurchaseLog_ItemMoney]  DEFAULT ((0)) FOR [ItemMoney]
GO

ALTER TABLE [dbo].[GISPurchaseLog] ADD  CONSTRAINT [DF_GISPurchaseLog_Data]  DEFAULT (getdate()) FOR [Date]
GO

ALTER TABLE [dbo].[GISPurchaseLog] ADD  CONSTRAINT [DF_GISPurchaseLog_UserID]  DEFAULT ('') FOR [UserID]
GO


