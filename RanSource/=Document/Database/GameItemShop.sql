USE [RanShop]
GO

/****** Object:  Table [dbo].[GameItemShop]    Script Date: 27/12/2021 9:51:07 pm ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[GameItemShop](
	[idx] [int] IDENTITY(1,1) NOT NULL,
	[ProductNum] [int] NOT NULL,
	[ItemMain] [int] NOT NULL,
	[ItemSub] [int] NOT NULL,
	[ItemCategory] [int] NOT NULL,
	[ItemStock] [int] NOT NULL,
	[ItemMoney] [int] NOT NULL,
	[ItemName] [varchar](64) NOT NULL,
	[ShopType] [int] NOT NULL,
 CONSTRAINT [PK_GameItemShop] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ProductNum]  DEFAULT ((0)) FOR [ProductNum]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ItemMain]  DEFAULT ((0)) FOR [ItemMain]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ItemSub]  DEFAULT ((0)) FOR [ItemSub]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ItemCategory]  DEFAULT ((0)) FOR [ItemCategory]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ItemStock]  DEFAULT ((0)) FOR [ItemStock]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_Table_1_ItemPrice]  DEFAULT ((0)) FOR [ItemMoney]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ItemName]  DEFAULT ('') FOR [ItemName]
GO

ALTER TABLE [dbo].[GameItemShop] ADD  CONSTRAINT [DF_GameItemShop_ShopType]  DEFAULT ((1)) FOR [ShopType]
GO


