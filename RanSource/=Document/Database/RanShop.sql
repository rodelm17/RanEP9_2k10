USE [master]
GO
/****** Object:  Database [RanShop]    Script Date: 1/23/2024 10:57:31 AM ******/
CREATE DATABASE [RanShop]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'RanShop', FILENAME = N'd:\_database_files\RanShop_Data.mdf' , SIZE = 8128KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10% )
 LOG ON 
( NAME = N'RanShop_log', FILENAME = N'd:\_database_files\RanShop_Log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [RanShop] SET COMPATIBILITY_LEVEL = 90
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [RanShop].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [RanShop] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [RanShop] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [RanShop] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [RanShop] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [RanShop] SET ARITHABORT OFF 
GO
ALTER DATABASE [RanShop] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [RanShop] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [RanShop] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [RanShop] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [RanShop] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [RanShop] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [RanShop] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [RanShop] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [RanShop] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [RanShop] SET  DISABLE_BROKER 
GO
ALTER DATABASE [RanShop] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [RanShop] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [RanShop] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [RanShop] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [RanShop] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [RanShop] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [RanShop] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [RanShop] SET RECOVERY FULL 
GO
ALTER DATABASE [RanShop] SET  MULTI_USER 
GO
ALTER DATABASE [RanShop] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [RanShop] SET DB_CHAINING OFF 
GO
ALTER DATABASE [RanShop] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [RanShop] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
EXEC sys.sp_db_vardecimal_storage_format N'RanShop', N'ON'
GO
USE [RanShop]
GO
/****** Object:  User [user]    Script Date: 1/23/2024 10:57:31 AM ******/
CREATE USER [user] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  Table [dbo].[GameItemShop]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
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
/****** Object:  Table [dbo].[GISPurchaseLog]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
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
/****** Object:  Table [dbo].[LogShopPurchase]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogShopPurchase](
	[PurNum] [bigint] IDENTITY(1,1) NOT NULL,
	[PurKey] [varchar](21) NOT NULL,
	[PurFlag] [int] NULL,
	[PurDate] [datetime] NULL,
 CONSTRAINT [PK_LogShopPurchase] PRIMARY KEY CLUSTERED 
(
	[PurNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ShopItemMap]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ShopItemMap](
	[ProductNum] [int] IDENTITY(1,1) NOT NULL,
	[ItemMain] [int] NULL,
	[ItemSub] [int] NULL,
	[ItemName] [varchar](100) NULL,
	[ItemList] [smallint] NULL,
	[Duration] [varchar](50) NULL,
	[Category] [varchar](50) NULL,
	[ItemStock] [int] NOT NULL,
	[ItemImage] [varchar](300) NULL,
	[ItemMoney] [int] NULL,
	[ItemComment] [varchar](50) NULL,
	[XD_Existing] [int] NOT NULL,
	[XD_CatName] [varchar](100) NULL,
	[XD_Date] [datetime] NOT NULL,
 CONSTRAINT [PK_ShopItemMap] PRIMARY KEY CLUSTERED 
(
	[ProductNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ShopPurchase]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ShopPurchase](
	[PurKey] [bigint] IDENTITY(1,1) NOT NULL,
	[UserUID] [varchar](20) NOT NULL,
	[ProductNum] [int] NOT NULL,
	[PurPrice] [int] NOT NULL,
	[PurFlag] [int] NOT NULL,
	[PurDate] [datetime] NOT NULL,
	[PurChgDate] [datetime] NULL,
	[ItemMain] [int] NULL,
	[ItemSub] [int] NULL,
	[XD_PurPack] [varchar](50) NULL,
	[XD_PurPackCode] [varchar](50) NULL,
	[XD_Deleted] [int] NOT NULL,
	[XD_ReInsert] [datetime] NULL,
 CONSTRAINT [PK_ShopPurchase] PRIMARY KEY CLUSTERED 
(
	[PurKey] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ShopPurFlag]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ShopPurFlag](
	[PurFlag] [int] NOT NULL,
	[PurFlagName] [varchar](20) NULL,
 CONSTRAINT [PK_ShopPurFlag] PRIMARY KEY CLUSTERED 
(
	[PurFlag] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[XD_adm_InsertItemLog]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[XD_adm_InsertItemLog](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[ProductNum] [int] NOT NULL,
	[ItemMain] [int] NULL,
	[ItemSub] [int] NULL,
	[AdminID] [varchar](50) NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_ShopPurchaseLog] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[XD_adm_ItemExisting]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[XD_adm_ItemExisting](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ItemMain] [int] NULL,
	[ItemSub] [int] NULL,
	[ItemName] [varchar](200) NULL,
	[Mark] [int] NULL,
	[Exist] [int] NULL,
	[Marker] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[XD_web_Category]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[XD_web_Category](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Parent] [int] NOT NULL,
	[Category] [varchar](100) NOT NULL,
	[Access] [smallint] NOT NULL,
	[Discount] [int] NOT NULL,
	[Promo] [int] NOT NULL,
 CONSTRAINT [PK_Webshop_Category] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[XD_web_Shop]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[XD_web_Shop](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ProductNum] [int] NOT NULL,
	[ItemMain] [int] NULL,
	[ItemSub] [int] NULL,
	[ItemName] [varchar](100) NULL,
	[ItemList] [smallint] NULL,
	[Duration] [varchar](50) NULL,
	[Category] [int] NOT NULL,
	[ItemStock] [int] NOT NULL,
	[ItemImage] [varchar](300) NULL,
	[ItemMoney] [int] NULL,
	[ItemComment] [varchar](100) NULL,
	[Edited] [datetime] NULL,
	[Sold] [int] NOT NULL,
	[CatID] [varchar](50) NULL,
	[ItemKind] [int] NOT NULL,
 CONSTRAINT [PK_XD_web_Shop] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[viewShopPurchase]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-------------------------------------------------------------------------------
-- viewShopPurchase
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewShopPurchase]
AS
SELECT   dbo.ShopPurchase.PurKey, dbo.ShopPurchase.UserUID, 
         dbo.ShopPurchase.ProductNum, dbo.ShopPurchase.PurPrice, 
         dbo.ShopPurchase.PurFlag, dbo.ShopPurchase.PurDate, 
         dbo.ShopPurchase.PurChgDate, dbo.ShopItemMap.ItemMain, 
         dbo.ShopItemMap.ItemSub, dbo.ShopItemMap.ItemName, 
         dbo.ShopPurFlag.PurFlagName
FROM     dbo.ShopPurchase INNER JOIN
         dbo.ShopItemMap ON 
         dbo.ShopPurchase.ProductNum = dbo.ShopItemMap.ProductNum LEFT OUTER JOIN
         dbo.ShopPurFlag ON dbo.ShopPurchase.PurFlag = dbo.ShopPurFlag.PurFlag

GO
/****** Object:  View [dbo].[viewShopPurchaseItem]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-------------------------------------------------------------------------------
-- view_ShopPurchaseItem.sql
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewShopPurchaseItem]
AS
SELECT TOP 100 PERCENT SUM(A.PurPrice) AS tPrice, A.ItemMain, A.ItemSub, B.ItemName
FROM   dbo.viewShopPurchase A INNER JOIN
       dbo.ShopItemMap B ON A.ProductNum = B.ProductNum
GROUP BY A.ItemMain, A.ItemSub, B.ItemName
ORDER BY A.ItemMain, A.ItemSub

GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_LogShopPurchase_PurKey]    Script Date: 1/23/2024 10:57:31 AM ******/
CREATE NONCLUSTERED INDEX [IX_LogShopPurchase_PurKey] ON [dbo].[LogShopPurchase]
(
	[PurKey] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
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
ALTER TABLE [dbo].[LogShopPurchase] ADD  CONSTRAINT [DF_LogShopPurchase_PurDate]  DEFAULT (getdate()) FOR [PurDate]
GO
ALTER TABLE [dbo].[ShopItemMap] ADD  CONSTRAINT [DF_ShopItemMap_ItemList]  DEFAULT ((1)) FOR [ItemList]
GO
ALTER TABLE [dbo].[ShopItemMap] ADD  CONSTRAINT [DF__ShopItemM__ItemS__38996AB5]  DEFAULT ((0)) FOR [ItemStock]
GO
ALTER TABLE [dbo].[ShopItemMap] ADD  CONSTRAINT [DF_ShopItemMap_XD_Date]  DEFAULT (getdate()) FOR [XD_Date]
GO
ALTER TABLE [dbo].[ShopPurchase] ADD  CONSTRAINT [DF_ShopPurchase_PurPrice]  DEFAULT ((0)) FOR [PurPrice]
GO
ALTER TABLE [dbo].[ShopPurchase] ADD  CONSTRAINT [DF_ShopPurchase_PurFlag]  DEFAULT ((0)) FOR [PurFlag]
GO
ALTER TABLE [dbo].[ShopPurchase] ADD  CONSTRAINT [DF_ShopPurchase_PurDate]  DEFAULT (getdate()) FOR [PurDate]
GO
ALTER TABLE [dbo].[ShopPurchase] ADD  CONSTRAINT [DF_ShopPurchase_Deleted]  DEFAULT ((0)) FOR [XD_PurPack]
GO
ALTER TABLE [dbo].[ShopPurchase] ADD  CONSTRAINT [DF_ShopPurchase_XD_PurPackCode]  DEFAULT ((0)) FOR [XD_PurPackCode]
GO
ALTER TABLE [dbo].[ShopPurchase] ADD  CONSTRAINT [DF_ShopPurchase_XD_Deleted]  DEFAULT ((0)) FOR [XD_Deleted]
GO
ALTER TABLE [dbo].[XD_adm_InsertItemLog] ADD  CONSTRAINT [DF_XD_adm_InsertItemLog_AdminID]  DEFAULT ('') FOR [AdminID]
GO
ALTER TABLE [dbo].[XD_adm_InsertItemLog] ADD  CONSTRAINT [DF_XD_adm_InsertItemLog_Date]  DEFAULT (getdate()) FOR [Date]
GO
ALTER TABLE [dbo].[XD_adm_ItemExisting] ADD  CONSTRAINT [DF_ItemExisting_NotExist]  DEFAULT ((0)) FOR [Exist]
GO
ALTER TABLE [dbo].[XD_web_Category] ADD  CONSTRAINT [DF_WebshopCategory_Parent]  DEFAULT ((0)) FOR [Parent]
GO
ALTER TABLE [dbo].[XD_web_Category] ADD  CONSTRAINT [DF_WebshopCategory_Access]  DEFAULT ((0)) FOR [Access]
GO
ALTER TABLE [dbo].[XD_web_Category] ADD  CONSTRAINT [DF_WebshopCategory_Discount]  DEFAULT ((100)) FOR [Discount]
GO
ALTER TABLE [dbo].[XD_web_Category] ADD  CONSTRAINT [DF_WebshopCategory_Promo]  DEFAULT ((0)) FOR [Promo]
GO
ALTER TABLE [dbo].[XD_web_Shop] ADD  CONSTRAINT [DF_FullItemMap_ItemList]  DEFAULT ((1)) FOR [ItemList]
GO
ALTER TABLE [dbo].[XD_web_Shop] ADD  CONSTRAINT [DF__FullItemM__ItemS__38996AB5]  DEFAULT ((0)) FOR [ItemStock]
GO
ALTER TABLE [dbo].[XD_web_Shop] ADD  CONSTRAINT [DF_Webshop_Sold]  DEFAULT ((0)) FOR [Sold]
GO
ALTER TABLE [dbo].[XD_web_Shop] ADD  CONSTRAINT [DF_Webshop_ItemKind]  DEFAULT ((0)) FOR [ItemKind]
GO
/****** Object:  StoredProcedure [dbo].[sp_GISPurchase]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_GISPurchase]
	@nIndex int,
	@nItemMID int,
	@nItemSID int,
	@nUserNum int,
	@UserId varchar(50),
	@nReturn int OUTPUT
AS	

DECLARE	
	@productNum int,
	@productStock int,
	@productType int,
	@productMoney int,
	@userNum int,
	@error_var int, -- Declare variables used in error checking.
	@rowcount_var int

SET NOCOUNT ON;

SELECT @productNum = ProductNum, @productStock = ItemStock, @productType = ShopType, @productMoney = ItemMoney
FROM GameItemShop (NOLOCK) 
WHERE idx = @nIndex and ItemMain = @nItemMID and ItemSub = @nItemSID --this should be enough of an identity

IF @error_var <> 0 OR @rowcount_var = 0
BEGIN
	SET @nReturn = 1 -- item not found
	SET NOCOUNT OFF
	RETURN @nReturn	
END

IF @productStock = 0
BEGIN
	SET @nReturn = 2 -- no stocks
	SET NOCOUNT OFF
	RETURN @nReturn	
END 


IF @productType = 0
BEGIN
	SET @nReturn = 3 -- product type is zero, not for purchase
	SET NOCOUNT OFF
	RETURN @nReturn	
END


--insert item
INSERT INTO ShopPurchase (UserUID, ProductNum, PurFlag, PurDate, PurChgDate, ItemMain, ItemSub )
VALUES( @UserId, @productNum, 0, GETDATE(), GETDATE(), @nItemMID, @nItemSID )

IF @@ERROR <> 0 
BEGIN 
	SET @nReturn = -1 --insert failed
	SET NOCOUNT OFF
	RETURN @nReturn	
END

--update stocks
UPDATE GameItemShop
SET ItemStock = ItemStock - 1
WHERE idx = @nIndex


--log
INSERT INTO GISPurchaseLog (ProductNum, ItemMain, ItemSub, ItemMoney, UserID)
VALUES( @productNum, @nItemMID, @nItemSID, @productMoney, @UserId )


SET @nReturn = 0 -- all goods
SET NOCOUNT OFF;
RETURN @nReturn

 
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertItem]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_InsertItem]
	@PurKey	varchar(100),
	@UserId varchar(50),
	@MID int,
	@SID int,
	@nReturn int OUTPUT
AS	
/*
Created by PrinceOfPersia
August 8, 2011
*/
DECLARE	@productNum int;

SET NOCOUNT ON;
	
BEGIN TRAN	

SET @nReturn = -1;
	
SELECT @productNum  = ProductNum FROM ShopItemMap (NOLOCK) 
WHERE ItemMain = @MID and ItemSub = @SID;

INSERT INTO ShopPurchase 
(
UserUID,
ProductNum,
PurFlag,
PurDate,
PurChgDate
)
VALUES
(
@UserId,
@productNum,
0,
GETDATE(),
GETDATE()
)

IF @@ERROR = 0 
	BEGIN 
		COMMIT TRAN;
		SET @nReturn = 0;
	END

SET NOCOUNT OFF;

RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_purchase_change_state]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[sp_purchase_change_state]
	@purkey varchar(22),
    @purflag int,
	@nReturn int OUTPUT
AS
	DECLARE 	
		@error_var int, -- Declare variables used in error checking.
		@rowcount_var int,
		@nFlag int

	SET NOCOUNT ON
	
	SET @nFlag = 0
	
	SELECT @nFlag=PurFlag 
	FROM ShopPurchase 
	WHERE PurKey=@purkey
	
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
	    SET @nReturn = 0
	    SET NOCOUNT OFF
	    RETURN @nReturn	
	END
	
	-- 官操妨绰 内靛客 泅犁 内靛啊 鞍篮 版快 俊矾
	IF @nFlag = @purflag
	BEGIN
	    SET @nReturn = 0
	    SET NOCOUNT OFF
	    RETURN @nReturn	
	END
	
	-- 沥犬窍霸 官曹荐 乐绰 版快
    UPDATE ShopPurchase
    SET PurFlag=@purflag, PurChgDate=getdate() 
    WHERE PurKey=@purkey

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
	    -- 角菩
	    SET @nReturn = 0
	END
    ELSE
    BEGIN
	    -- 己傍
	    INSERT INTO LogShopPurchase (PurKey, PurFlag) 
	    VALUES (@purkey, @purflag)
	    SET @nReturn = 1
    END

	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_purchase_insert_item]    Script Date: 1/23/2024 10:57:31 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[sp_purchase_insert_item]
	@purkey varchar(22),
	@useruid varchar(30),
    @productnum int,
    @purprice int,
	@nReturn int OUTPUT
AS
	DECLARE 	
		@error_var int -- Declare variables used in error checking.

	SET NOCOUNT ON

	INSERT INTO ShopPurchase (PurKey, UserUID, ProductNum, PurPrice) 
	VALUES (@purkey, @useruid, @productnum, @purprice)

	SELECT @error_var = @@ERROR
	IF @error_var <> 0 
	BEGIN
	    -- 火涝角菩
	    SET @nReturn = 0	    
	END
        ELSE
        BEGIN
	    -- 沥惑利栏肺 火涝 己傍
	    SET @nReturn = 1
        END

	SET NOCOUNT OFF

	RETURN @nReturn	
GO
USE [master]
GO
ALTER DATABASE [RanShop] SET  READ_WRITE 
GO
