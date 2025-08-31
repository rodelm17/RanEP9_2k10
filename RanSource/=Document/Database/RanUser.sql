USE [master]
GO
/****** Object:  Database [RanUser]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE DATABASE [RanUser]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'RanUser', FILENAME = N'D:\[Database]\Ran\RanUser_Data.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10%)
 LOG ON 
( NAME = N'RanUser_log', FILENAME = N'D:\[Database]\Ran\RanUser_Log.ldf' , SIZE = 2048KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10%)
GO
ALTER DATABASE [RanUser] SET COMPATIBILITY_LEVEL = 100
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [RanUser].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [RanUser] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [RanUser] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [RanUser] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [RanUser] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [RanUser] SET ARITHABORT OFF 
GO
ALTER DATABASE [RanUser] SET AUTO_CLOSE ON 
GO
ALTER DATABASE [RanUser] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [RanUser] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [RanUser] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [RanUser] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [RanUser] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [RanUser] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [RanUser] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [RanUser] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [RanUser] SET  DISABLE_BROKER 
GO
ALTER DATABASE [RanUser] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [RanUser] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [RanUser] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [RanUser] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [RanUser] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [RanUser] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [RanUser] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [RanUser] SET RECOVERY FULL 
GO
ALTER DATABASE [RanUser] SET  MULTI_USER 
GO
ALTER DATABASE [RanUser] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [RanUser] SET DB_CHAINING OFF 
GO
ALTER DATABASE [RanUser] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [RanUser] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
USE [RanUser]
GO
/****** Object:  User [user]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE USER [user] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  Table [dbo].[ServerGroup]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ServerGroup](
	[SGNum] [int] NOT NULL,
	[SGName] [varchar](50) NOT NULL,
	[OdbcName] [varchar](50) NOT NULL,
	[OdbcUserID] [varchar](20) NOT NULL,
	[OdbcPassword] [varchar](20) NOT NULL,
	[OdbcLogName] [varchar](50) NOT NULL,
	[OdbcLogUserID] [varchar](20) NOT NULL,
	[OdbcLogPassword] [varchar](20) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[SGNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ServerInfo]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ServerInfo](
	[SGNum] [int] NOT NULL,
	[SvrNum] [int] NOT NULL,
	[SvrType] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[SvrNum] ASC,
	[SGNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[viewServerList]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

-------------------------------------------------------------------------------
-- view_ServerList.sql
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewServerList]
AS
SELECT  A.SGNum, A.SvrNum, A.SvrType, B.SGName, 
        B.OdbcName, B.OdbcUserID, B.OdbcPassword,
        B.OdbcLogName, B.OdbcLogUserID, B.OdbcLogPassword
FROM    dbo.ServerInfo A LEFT OUTER JOIN
        dbo.ServerGroup B ON A.SGNum = B.SGNum
WHERE   (A.SvrType = 4)
GO
/****** Object:  Table [dbo].[LogGameTime]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogGameTime](
	[GameTimeNum] [bigint] IDENTITY(1,1) NOT NULL,
	[LogDate] [datetime] NOT NULL,
	[GameTime] [int] NOT NULL,
	[UserID] [varchar](20) NULL,
	[UserNum] [int] NULL,
	[SGNum] [int] NULL,
	[SvrNum] [int] NULL,
	[ChaNum] [int] NULL,
 CONSTRAINT [PK_LogGameTime] PRIMARY KEY CLUSTERED 
(
	[GameTimeNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[viewLogGameTime]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-------------------------------------------------------------------------------
-- viewLogGameTime
-------------------------------------------------------------------------------
CREATE VIEW [dbo].[viewLogGameTime] AS
SELECT GameTimeNum, LogDate, GameTime, UserID, UserNum, SGNum, SvrNum, ChaNum
FROM LogGameTime
GO
/****** Object:  Table [dbo].[LogLogin]    Script Date: 7/28/2021 2:45:13 AM ******/
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
	[LogPCID] [varchar](65) NULL,
 CONSTRAINT [PK_LogLogin] PRIMARY KEY CLUSTERED 
(
	[LoginNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[viewLogLogin]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-------------------------------------------------------------------------------
-- viewLogLogin
-------------------------------------------------------------------------------
Create view [dbo].[viewLogLogin] AS
SELECT  LoginNum, UserNum, UserID, LogInOut, LogDate, LogIpAddress
FROM LogLogin
GO
/****** Object:  Table [dbo].[BlockAddress]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BlockAddress](
	[BlockIdx] [int] IDENTITY(1,1) NOT NULL,
	[BlockAddress] [varchar](23) NOT NULL,
	[BlockReason] [varchar](256) NULL,
	[BlockDate] [datetime] NULL,
 CONSTRAINT [PK_BlockAddress] PRIMARY KEY CLUSTERED 
(
	[BlockIdx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[BlockPCID]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BlockPCID](
	[BlockIdx] [int] IDENTITY(1,1) NOT NULL,
	[BlockHWID] [varchar](65) NOT NULL,
	[BlockMAC] [varchar](65) NOT NULL,
	[BlockTYPE] [bigint] NOT NULL,
	[BlockReason] [varchar](512) NULL,
	[BlockDate] [datetime] NULL,
 CONSTRAINT [PK_BlockPCID] PRIMARY KEY CLUSTERED 
(
	[BlockIdx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[CheckId]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CheckId](
	[Num] [int] IDENTITY(1,1) NOT NULL,
	[Id] [varchar](18) NOT NULL,
	[CreateDate] [datetime] NULL,
 CONSTRAINT [PK_CheckId] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[FullUserInfo]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[FullUserInfo](
	[UserNum] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [varchar](20) NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[UserPass] [varchar](20) NOT NULL,
	[UserPass2] [varchar](20) NOT NULL,
	[BodyID] [varchar](18) NOT NULL,
	[Sex] [varchar](2) NOT NULL,
	[Email] [varchar](50) NOT NULL,
	[BirthY] [varchar](4) NOT NULL,
	[BirthM] [varchar](2) NOT NULL,
	[BirthD] [varchar](2) NOT NULL,
	[TEL] [varchar](15) NOT NULL,
	[Mobile] [varchar](13) NULL,
	[QQ] [varchar](13) NULL,
	[MSN] [varchar](50) NULL,
	[City1] [varchar](20) NOT NULL,
	[City2] [varchar](20) NOT NULL,
	[Post] [varchar](6) NULL,
	[Address] [varchar](60) NULL,
	[SafeId] [varchar](12) NOT NULL,
	[BodyID2] [varchar](18) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[gmc]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[gmc](
	[username] [nvarchar](50) NULL,
	[session] [varchar](max) NULL,
	[sesexp] [varchar](max) NULL
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[HWIDWatchlist]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[HWIDWatchlist](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[HWID] [varchar](65) NOT NULL,
	[Date] [datetime] NOT NULL,
	[Note] [varchar](1024) NULL,
 CONSTRAINT [PK_HWIDWatchlist] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[IPInfo]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[IPInfo](
	[IpAddress] [varchar](23) NOT NULL,
	[UserNum] [int] NOT NULL,
	[IdxIP] [int] IDENTITY(1,1) NOT NULL,
	[UseAvailable] [int] NULL,
 CONSTRAINT [PK_IPInfo] PRIMARY KEY CLUSTERED 
(
	[IdxIP] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogChatBlock]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogChatBlock](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[UserNum] [bigint] NOT NULL,
	[UserID] [varchar](33) NOT NULL,
	[ChatBlockDate] [datetime] NOT NULL,
	[ChatBlockReason] [varchar](512) NOT NULL,
	[GMUserNum] [bigint] NOT NULL,
	[GMUserID] [varchar](33) NOT NULL,
 CONSTRAINT [PK_LogChatBlock] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogExistLogin]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
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
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogGmCmd]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogGmCmd](
	[GmCmdNum] [int] IDENTITY(1,1) NOT NULL,
	[LogDate] [datetime] NULL,
	[GmCmd] [varchar](200) NULL,
	[UserNum] [int] NULL,
 CONSTRAINT [PK_LogGmCmd] PRIMARY KEY CLUSTERED 
(
	[GmCmdNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogLoginDeviceCheck]    Script Date: 7/28/2021 2:45:13 AM ******/
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
/****** Object:  Table [dbo].[MasterLogLogin]    Script Date: 7/28/2021 2:45:13 AM ******/
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
/****** Object:  Table [dbo].[MasterPasswords]    Script Date: 7/28/2021 2:45:13 AM ******/
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
/****** Object:  Table [dbo].[newcheckid]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[newcheckid](
	[Id] [varchar](18) NOT NULL,
	[CreateDate] [datetime] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[StatGameTime]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[StatGameTime](
	[GYear] [int] NOT NULL,
	[GMonth] [int] NOT NULL,
	[GDay] [int] NOT NULL,
	[GTime] [int] NULL,
 CONSTRAINT [PK_StatGameTime] PRIMARY KEY CLUSTERED 
(
	[GYear] ASC,
	[GMonth] ASC,
	[GDay] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[StatLogin]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[StatLogin](
	[LYear] [int] NOT NULL,
	[LMonth] [int] NOT NULL,
	[LDay] [int] NOT NULL,
	[LHour] [int] NOT NULL,
	[LCount] [int] NULL,
 CONSTRAINT [PK_StatLogin] PRIMARY KEY CLUSTERED 
(
	[LYear] ASC,
	[LMonth] ASC,
	[LDay] ASC,
	[LHour] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TB_CC_IP]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_CC_IP](
	[IpNum] [int] NOT NULL,
	[CC_Class] [varchar](50) NULL,
	[CC_IP] [varchar](50) NULL,
	[Username] [varchar](50) NULL,
	[IcafeCode] [varchar](50) NULL,
 CONSTRAINT [PK_TB_CC_IP] PRIMARY KEY CLUSTERED 
(
	[IpNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UserInfo]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserInfo](
	[UserNum] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [varchar](20) NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[UserPass] [varchar](20) NOT NULL,
	[UserPass_N] [varchar](50) NOT NULL,
	[UserPass2] [varchar](20) NOT NULL,
	[UserPass2_N] [varchar](50) NOT NULL,
	[UserType] [int] NOT NULL,
	[UserLoginState] [int] NOT NULL,
	[UserAvailable] [int] NULL,
	[CreateDate] [datetime] NOT NULL,
	[LastLoginDate] [datetime] NOT NULL,
	[SGNum] [int] NULL,
	[SvrNum] [int] NULL,
	[ChaName] [varchar](33) NULL,
	[UserBlock] [int] NOT NULL,
	[UserBlockDate] [datetime] NOT NULL,
	[ChaRemain] [int] NOT NULL,
	[ChaTestRemain] [int] NOT NULL,
	[PremiumDate] [datetime] NOT NULL,
	[ChatBlockDate] [datetime] NOT NULL,
	[UserEmail] [varchar](50) NULL,
	[UserPoint] [int] NOT NULL,
	[WebLoginState] [varchar](50) NULL,
	[UserAge] [int] NULL,
	[OfflineTime] [bigint] NOT NULL,
	[GameTime] [bigint] NOT NULL,
	[UserIP] [varchar](50) NULL,
	[UserLastLoginDate] [datetime] NULL,
	[PlayTime] [bigint] NOT NULL,
	[Donated] [int] NULL,
	[UserSA] [varchar](33) NOT NULL,
	[UserFullName] [varchar](50) NOT NULL,
	[UserFlagVerified] [bigint] NOT NULL,
	[UserFlagRestricted] [bigint] NOT NULL,
	[UserPCIDHWID] [varchar](65) NULL,
	[UserPCIDMAC] [varchar](65) NULL,
	[UserPCID] [varchar](65) NULL,
	[LastPCIDHWID] [varchar](65) NOT NULL,
	[LastPCIDMAC] [varchar](65) NOT NULL,
	[LastIP] [varchar](65) NOT NULL,
	[UserLoginDeviceCheck] [int] NOT NULL,
 CONSTRAINT [PK_UserInfo] PRIMARY KEY CLUSTERED 
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [IX_UserInfoUserID] UNIQUE NONCLUSTERED 
(
	[UserID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UserKey]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserKey](
	[Num] [int] IDENTITY(1,1) NOT NULL,
	[PCIDHWID] [varchar](65) NOT NULL,
	[PCIDMAC] [varchar](65) NOT NULL,
	[PCIDUserNum] [bigint] NOT NULL,
	[PCIDUserID] [varchar](33) NOT NULL,
	[PCIDSGNum] [bigint] NOT NULL,
	[PCIDDate] [datetime] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UserProfile]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserProfile](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[UserFullName] [varchar](50) NOT NULL,
 CONSTRAINT [PK_UserProfile] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_BlockAddress]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE UNIQUE NONCLUSTERED INDEX [IX_BlockAddress] ON [dbo].[BlockAddress]
(
	[BlockAddress] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_LogGameTime_UserID]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE NONCLUSTERED INDEX [IX_LogGameTime_UserID] ON [dbo].[LogGameTime]
(
	[UserID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [IX_LogGameTime_UserNum]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE NONCLUSTERED INDEX [IX_LogGameTime_UserNum] ON [dbo].[LogGameTime]
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [IX_LogGmCmd]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE NONCLUSTERED INDEX [IX_LogGmCmd] ON [dbo].[LogGmCmd]
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_LogLogin_UserID]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE NONCLUSTERED INDEX [IX_LogLogin_UserID] ON [dbo].[LogLogin]
(
	[UserID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [IX_LogLogin_UserNum]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE NONCLUSTERED INDEX [IX_LogLogin_UserNum] ON [dbo].[LogLogin]
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
/****** Object:  Index [IX_ServerInfo]    Script Date: 7/28/2021 2:45:13 AM ******/
CREATE NONCLUSTERED INDEX [IX_ServerInfo] ON [dbo].[ServerInfo]
(
	[SGNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
GO
ALTER TABLE [dbo].[BlockAddress] ADD  CONSTRAINT [DF_BlockAddress_BlockDate]  DEFAULT (getdate()) FOR [BlockDate]
GO
ALTER TABLE [dbo].[BlockPCID] ADD  CONSTRAINT [DF_BlockPCID_BlockHWID]  DEFAULT ('') FOR [BlockHWID]
GO
ALTER TABLE [dbo].[BlockPCID] ADD  CONSTRAINT [DF_BlockPCID_BlockMAC]  DEFAULT ('') FOR [BlockMAC]
GO
ALTER TABLE [dbo].[BlockPCID] ADD  CONSTRAINT [DF_BlockPCID_BlockTYPE]  DEFAULT ((0)) FOR [BlockTYPE]
GO
ALTER TABLE [dbo].[BlockPCID] ADD  CONSTRAINT [DF_BlockPCID_BlockDate]  DEFAULT (getdate()) FOR [BlockDate]
GO
ALTER TABLE [dbo].[FullUserInfo] ADD  CONSTRAINT [DF_FullUserInfo_UserName]  DEFAULT ('') FOR [UserName]
GO
ALTER TABLE [dbo].[FullUserInfo] ADD  CONSTRAINT [DF_FullUserInfo_UserID]  DEFAULT ('') FOR [UserID]
GO
ALTER TABLE [dbo].[FullUserInfo] ADD  CONSTRAINT [DF_FullUserInfo_UserPass]  DEFAULT ('') FOR [UserPass]
GO
ALTER TABLE [dbo].[FullUserInfo] ADD  CONSTRAINT [DF_FullUserInfo_UserPass2]  DEFAULT ('') FOR [UserPass2]
GO
ALTER TABLE [dbo].[FullUserInfo] ADD  CONSTRAINT [DF_FullUserInfo_BodyID]  DEFAULT ('') FOR [BodyID]
GO
ALTER TABLE [dbo].[HWIDWatchlist] ADD  CONSTRAINT [DF_HWIDWatchlist_HWID]  DEFAULT ('') FOR [HWID]
GO
ALTER TABLE [dbo].[HWIDWatchlist] ADD  CONSTRAINT [DF_HWIDWatchlist_Date]  DEFAULT (getdate()) FOR [Date]
GO
ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO
ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_UserID]  DEFAULT ('') FOR [UserID]
GO
ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_ChatBlockDate]  DEFAULT ('1970-02-01') FOR [ChatBlockDate]
GO
ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_ChatBlockReason]  DEFAULT ('') FOR [ChatBlockReason]
GO
ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_GMUserNum]  DEFAULT ((0)) FOR [GMUserNum]
GO
ALTER TABLE [dbo].[LogChatBlock] ADD  CONSTRAINT [DF_LogChatBlock_GMUserID]  DEFAULT ('') FOR [GMUserID]
GO
ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO
ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_UserID]  DEFAULT ('') FOR [UserID]
GO
ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_LogIpAddress]  DEFAULT ('') FOR [LogIpAddress]
GO
ALTER TABLE [dbo].[LogExistLogin] ADD  CONSTRAINT [DF_LogExistLogin_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO
ALTER TABLE [dbo].[LogGameTime] ADD  CONSTRAINT [DF_LogGameTime_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO
ALTER TABLE [dbo].[LogGameTime] ADD  CONSTRAINT [DF_LogGameTime_GameTime]  DEFAULT ((0)) FOR [GameTime]
GO
ALTER TABLE [dbo].[LogGameTime] ADD  CONSTRAINT [DF_LogGameTime_UserNum]  DEFAULT ((0)) FOR [UserNum]
GO
ALTER TABLE [dbo].[LogGameTime] ADD  CONSTRAINT [DF_LogGameTime_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO
ALTER TABLE [dbo].[LogGameTime] ADD  CONSTRAINT [DF_LogGameTime_SvrNum]  DEFAULT ((0)) FOR [SvrNum]
GO
ALTER TABLE [dbo].[LogGameTime] ADD  CONSTRAINT [DF_LogGameTime_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[LogGmCmd] ADD  CONSTRAINT [DF_LogGmCmd_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO
ALTER TABLE [dbo].[LogLogin] ADD  CONSTRAINT [DF_LogLogin_LogInOut]  DEFAULT ((0)) FOR [LogInOut]
GO
ALTER TABLE [dbo].[LogLogin] ADD  CONSTRAINT [DF_LogLogin_LogDate]  DEFAULT (getdate()) FOR [LogDate]
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
ALTER TABLE [dbo].[MasterLogLogin] ADD  CONSTRAINT [DF_MasterLogLogin_LogDate]  DEFAULT (getdate()) FOR [LogDate]
GO
ALTER TABLE [dbo].[MasterPasswords] ADD  CONSTRAINT [DF_MasterPasswords_MasterPass]  DEFAULT ('') FOR [MasterPass]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_SGName]  DEFAULT ('') FOR [SGName]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_OdbcName]  DEFAULT ('') FOR [OdbcName]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_OdbcUserID]  DEFAULT ('') FOR [OdbcUserID]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_OdbcPassword]  DEFAULT ('') FOR [OdbcPassword]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_OdbcLogName]  DEFAULT ('') FOR [OdbcLogName]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_OdbcLogUserID]  DEFAULT ('') FOR [OdbcLogUserID]
GO
ALTER TABLE [dbo].[ServerGroup] ADD  CONSTRAINT [DF_ServerGroup_OdbcLogPassword]  DEFAULT ('') FOR [OdbcLogPassword]
GO
ALTER TABLE [dbo].[StatGameTime] ADD  CONSTRAINT [DF_StatGameTime_GYear]  DEFAULT (datepart(year,getdate())) FOR [GYear]
GO
ALTER TABLE [dbo].[StatGameTime] ADD  CONSTRAINT [DF_StatGameTime_GMonth]  DEFAULT (datepart(month,getdate())) FOR [GMonth]
GO
ALTER TABLE [dbo].[StatGameTime] ADD  CONSTRAINT [DF_StatGameTime_GDay]  DEFAULT (datepart(day,getdate())) FOR [GDay]
GO
ALTER TABLE [dbo].[StatGameTime] ADD  CONSTRAINT [DF_StatGameTime_GCount]  DEFAULT ((0)) FOR [GTime]
GO
ALTER TABLE [dbo].[StatLogin] ADD  CONSTRAINT [DF_StatLogin_LYear]  DEFAULT (datepart(year,getdate())) FOR [LYear]
GO
ALTER TABLE [dbo].[StatLogin] ADD  CONSTRAINT [DF_StatLogin_LMonth]  DEFAULT (datepart(month,getdate())) FOR [LMonth]
GO
ALTER TABLE [dbo].[StatLogin] ADD  CONSTRAINT [DF_StatLogin_LDay]  DEFAULT (datepart(day,getdate())) FOR [LDay]
GO
ALTER TABLE [dbo].[StatLogin] ADD  CONSTRAINT [DF_StatLogin_LHour]  DEFAULT (datepart(hour,getdate())) FOR [LHour]
GO
ALTER TABLE [dbo].[StatLogin] ADD  CONSTRAINT [DF_StatLogin_LCount]  DEFAULT ((1)) FOR [LCount]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserName]  DEFAULT ('') FOR [UserName]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserID]  DEFAULT ('') FOR [UserID]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserPass]  DEFAULT ('') FOR [UserPass]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserPass_N]  DEFAULT ('empty') FOR [UserPass_N]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserPass2]  DEFAULT ('') FOR [UserPass2]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserPass2_N]  DEFAULT ('empty') FOR [UserPass2_N]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserType]  DEFAULT ((1)) FOR [UserType]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserLoginState]  DEFAULT ((0)) FOR [UserLoginState]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserAvailable]  DEFAULT ((1)) FOR [UserAvailable]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_CreateDate]  DEFAULT (getdate()) FOR [CreateDate]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_LastLoginDate]  DEFAULT (getdate()) FOR [LastLoginDate]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_SvrNum]  DEFAULT ((0)) FOR [SvrNum]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_ChaName]  DEFAULT ('') FOR [ChaName]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserBlock]  DEFAULT ((0)) FOR [UserBlock]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserBlockDate]  DEFAULT (getdate()) FOR [UserBlockDate]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_ChaRemain]  DEFAULT ((2)) FOR [ChaRemain]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_ChaTestRemain]  DEFAULT ((2)) FOR [ChaTestRemain]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_PremiumDate]  DEFAULT ('2020-02-01') FOR [PremiumDate]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_ChatBlockDate]  DEFAULT ('1970-02-01') FOR [ChatBlockDate]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserPoint]  DEFAULT ((0)) FOR [UserPoint]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserAge]  DEFAULT ((18)) FOR [UserAge]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_OfflineTime]  DEFAULT ((-999999999)) FOR [OfflineTime]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_GameTime]  DEFAULT ((-999999999)) FOR [GameTime]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_PlayTime]  DEFAULT ((0)) FOR [PlayTime]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_Donated]  DEFAULT ((0)) FOR [Donated]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserSA]  DEFAULT ('') FOR [UserSA]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserFlagVerified]  DEFAULT ((0)) FOR [UserFlagVerified]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserFlagRestricted]  DEFAULT ((0)) FOR [UserFlagRestricted]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_LastPCIDHWID]  DEFAULT ('') FOR [LastPCIDHWID]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_LastPCIDMAC]  DEFAULT ('') FOR [LastPCIDMAC]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_LastIP]  DEFAULT ('') FOR [LastIP]
GO
ALTER TABLE [dbo].[UserInfo] ADD  CONSTRAINT [DF_UserInfo_UserLoginDeviceCheck]  DEFAULT ((0)) FOR [UserLoginDeviceCheck]
GO
ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDHWID]  DEFAULT ('') FOR [PCIDHWID]
GO
ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDMAC]  DEFAULT ('') FOR [PCIDMAC]
GO
ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDUserNum]  DEFAULT ((0)) FOR [PCIDUserNum]
GO
ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDUserID]  DEFAULT ('') FOR [PCIDUserID]
GO
ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDSGNum]  DEFAULT ((0)) FOR [PCIDSGNum]
GO
ALTER TABLE [dbo].[UserKey] ADD  CONSTRAINT [DF_UserKey_PCIDDate]  DEFAULT (getdate()) FOR [PCIDDate]
GO
/****** Object:  StoredProcedure [dbo].[gm_login]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

-------------------------------------------------------------------------------
-- sp_gm_login.sql
-------------------------------------------------------------------------------
CREATE      PROCEDURE [dbo].[gm_login]
	@userId		char(50),
	@userPass 	char(50),
	@nReturn 	int	OUTPUT
AS
	DECLARE @nUserNum	int,
		@nUserType	int

	SET NOCOUNT ON

	SET @nReturn = 0
	SET @nUserNum = 0
	
	SELECT @nUserNum = UserInfo.UserNum, @nUserType=UserInfo.UserType 
	FROM UserInfo 
	WHERE UserID = @userId AND UserPass = @userPass AND UserAvailable = 1 AND UserType>=20 

	-- ID / PWD 眉农...
	IF @nUserNum = 0
	BEGIN
		-- ID / PWD 阂老摹 肚绰 荤侩阂啊瓷惑怕
		SET @nReturn = 0
	END
	ELSE
	BEGIN
		-- ID / PWD 老摹
		SET @nReturn = @nUserType
		-- 立加肺弊 巢扁扁
		INSERT INTO LogGmCmd (UserNum, GmCmd) 
		VALUES (@nUserNum, 'LOGIN GMTOOL UserID:' + @userId)
	END	

	SET NOCOUNT OFF	
	
	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[HWIDWatchlistCheck]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[HWIDWatchlistCheck]
    @HWID  varchar(65), --PCID
	@MAC  varchar(65), --PCID
    @nReturn     int    OUTPUT
AS        
    SET NOCOUNT ON

    SET @nReturn = 0
   
	--hwid is in watchlist
	--ban the mac address
    IF (SELECT COUNT(*) FROM HWIDWatchlist WITH (NOLOCK) WHERE HWID = @HWID) > 0
	BEGIN
		SET @nReturn = 100
		
		--we use the hwid as reason for reference
		INSERT INTO BlockPCID ( BlockMAC, BlockTYPE, BlockReason ) 
        VALUES ( @MAC, 2, @HWID)    
	END
		
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_LogChatBlock]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_LogChatBlock]
	@nUserNum     int,
	@szUserID     varchar(33),
	@szBlockDate  varchar(65),
	@szReason     varchar(512), 
	@nGMUserNum   int,
	@szGMUserID   varchar(33),
	@nReturn      int    OUTPUT
AS
   DECLARE 
        @error_var int,
        @rowcount_var int

    SET NOCOUNT ON

    SET @nReturn = 0
    
	BEGIN TRAN
	
	INSERT INTO LogChatBlock ( UserNum, UserID, ChatBlockDate, ChatBlockReason, GMUserNum, GMUserID )
	VALUES ( @nUserNum, @szUserID, @szBlockDate, @szReason, @nGMUserNum, @szGMUserID )

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
		END
	ELSE
		BEGIN
		COMMIT TRAN
		END

    SET NOCOUNT OFF    
    
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_PCIDBlock]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_PCIDBlock]
	@szReason     varchar(512), 
	@szHWID       varchar(65),
	@szMAC        varchar(65),
	@nType        int,
	@nReturn      int    OUTPUT
AS
    DECLARE 
		@idx int,
        @error_var int,
        @rowcount_var int
        
	SET NOCOUNT ON
	
	--return -1 failed
	--return 0 success
	--return 1 exist
	SET @nReturn = 0
	
	IF @nType = 1
	BEGIN
		
		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockHWID = @szHWID AND BlockTYPE = 1) > 0
		BEGIN
			SET @nReturn = 1
			RETURN @nReturn
		END
	
		INSERT INTO BlockPCID (BlockHWID, BlockTYPE, BlockReason ) 
        VALUES (@szHWID, @nType, @szReason )   
        
        SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
		IF @error_var <> 0 OR @rowcount_var = 0
			BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
			END
		ELSE
			BEGIN
			COMMIT TRAN
		END
		 
	END
	
	IF @nType = 2
	BEGIN
		
        IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockMAC = @szMAC AND BlockTYPE = 2) > 0
		BEGIN
			SET @nReturn = 1
			RETURN @nReturn
		END
	    
	    INSERT INTO BlockPCID (BlockMAC, BlockTYPE, BlockReason ) 
        VALUES (@szMAC, @nType, @szReason )   
        
        SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
		IF @error_var <> 0 OR @rowcount_var = 0
			BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
			END
		ELSE
			BEGIN
			COMMIT TRAN
		END
		
	END
	
	IF @nType = 3
	BEGIN
	   
	    IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockHWID = @szHWID AND  BlockMAC = @szMAC AND BlockTYPE = 3 ) > 0
		BEGIN
			SET @nReturn = 1
			RETURN @nReturn
		END
	    
	    INSERT INTO BlockPCID (BlockHWID, BlockMAC, BlockTYPE, BlockReason ) 
        VALUES (@szHWID, @szMAC, @nType, @szReason )   
        
        SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
		IF @error_var <> 0 OR @rowcount_var = 0
			BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
			END
		ELSE
			BEGIN
			COMMIT TRAN
		END
		
	END
	
	
	
	
	
	
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UserRestrict]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_UserRestrict]
	 @UserNum int,
     @UserRestricted int,
     @nReturn int OUTPUT
	
AS
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET UserFlagRestricted = @UserRestricted
	WHERE UserNum = @UserNum

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaName]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdateChaName]
	@nUserNum int,
	@szChaName varchar (33)
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET ChaName=@szChaName
	WHERE UserNum=@nUserNum
	
	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaNumDecrease]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdateChaNumDecrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaRemain=ChaRemain-1
	WHERE UserNum=@nUserNum
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
       	SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
       	SET @nReturn = 0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaNumIncrease]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdateChaNumIncrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaRemain=ChaRemain+1
	WHERE UserNum=@nUserNum	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
       	SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
       	SET @nReturn = 0
		SET NOCOUNT OFF
		RETURN @nReturn
	END

GO
/****** Object:  StoredProcedure [dbo].[UpdateTestChaNumDecrease]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdateTestChaNumDecrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaTestRemain=ChaTestRemain-1
	WHERE UserNum=@nUserNum	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
       	SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
       	SET @nReturn = 0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
GO
/****** Object:  StoredProcedure [dbo].[UpdateTestChaNumIncrease]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdateTestChaNumIncrease]
	@nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET ChaTestRemain=ChaTestRemain+1
	WHERE UserNum=@nUserNum	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
       	SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
       	SET @nReturn = 0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
GO
/****** Object:  StoredProcedure [dbo].[user_account_page_login_device_check_set]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[user_account_page_login_device_check_set]
	@UserNum		int,
    @userId			char(25),
    @userPass		char(25),
	@UserLoginDeviceCheck		int,
    @SvrGrpNum		int,
    @SvrNum			int,   
    @nReturn		int    OUTPUT

AS        
    DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE UserInfo
	SET UserLoginDeviceCheck=@UserLoginDeviceCheck
	WHERE UserNum=@UserNum AND UserID=@userId AND UserPass2=@userPass
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		--not found error 1
       	SET @nReturn = 1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		--good return -
       	SET @nReturn = 0
		SET NOCOUNT OFF
		RETURN @nReturn
	END



GO
/****** Object:  StoredProcedure [dbo].[user_cha_remain]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[user_cha_remain]
	@nUserNum	int,
	@nReturn 	int	OUTPUT
AS	    
	DECLARE @nChaRemain int

	SET NOCOUNT ON

	SET @nReturn = 0
	SET @nChaRemain = 0
	
	SELECT @nChaRemain = UserInfo.ChaRemain
	FROM UserInfo
	WHERE UserNum = @nUserNum
	
	SET @nReturn = @nChaRemain

	SET NOCOUNT OFF	
	
	RETURN @nReturn


GO
/****** Object:  StoredProcedure [dbo].[user_cha_test_remain]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[user_cha_test_remain]
	@nUserNum	int,
	@nReturn 	int	OUTPUT
AS	    
	DECLARE @nChaRemain int

	SET NOCOUNT ON

	SET @nReturn = 0
	
	SELECT @nChaRemain = UserInfo.ChaTestRemain
	FROM UserInfo
	WHERE UserNum = @nUserNum
	
	SET @nReturn = @nChaRemain

	SET NOCOUNT OFF	
	
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[user_gettype]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[user_gettype]
	@nUserNum	int,
	@nReturn 	int	OUTPUT
AS	
    
	DECLARE @nUserType int

	SET NOCOUNT ON

	SET @nReturn = 0
	SET @nUserType = 0
	
	SELECT @nUserType = UserInfo.UserType 
	FROM UserInfo
	WHERE UserNum = @nUserNum
	
	SET @nReturn = @nUserType

	SET NOCOUNT OFF	
	
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[user_login_device_check_verify_request]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[user_login_device_check_verify_request]
    @userId			char(25),
    @userPass		char(25),
    @SvrGrpNum		int,
    @SvrNum			int,   
	@userIp			char(25),
    @pcID_HWID		varchar(65), --PCID
	@pcID_MAC		varchar(65), --PCID
    @nReturn		int    OUTPUT

AS        
    DECLARE 
		@nUserNum		int,
		@strLastHWID varchar(65),
		@strLastMAC varchar(65),
		@strLastIP varchar(25)

    SET NOCOUNT ON

	SET @nReturn = 0
	SET @nUserNum = 0

	SELECT @nUserNum = UserInfo.UserNum,
		   @strLastHWID = UserInfo.LastPCIDHWID,
		   @strLastMAC = UserInfo.LastPCIDMAC,
		   @strLastIP = UserInfo.LastIP
	FROM UserInfo
	WHERE UserID = @userId AND UserPass2 = @userPass AND UserLoginDeviceCheck = 1

	--user not found/wrong password2
	IF @nUserNum = 0
    BEGIN    
		SET @nReturn = 1        
        RETURN @nReturn
	END

	--set return as ok(0)
	SET @nReturn = 0   

	--update information
	UPDATE UserInfo
    SET LastPCIDHWID = @pcID_HWID, LastPCIDMAC = @pcID_MAC, LastIP = @userIp
    WHERE UserNum = @nUserNum

	--log changes
	INSERT INTO LogloginDeviceCheck (UserNum, UserID, PrevPCIDHWID, PrevPCIDMAC, PrevIP, NewPCIDHWID, NewPCIDMAC, NewIP ) 
    VALUES (@nUserNum, @userId, @strLastHWID, @strLastMAC, @strLastIP, @pcID_HWID, @pcID_MAC, @userIp )    

    SET NOCOUNT OFF    
    
    RETURN @nReturn  



GO
/****** Object:  StoredProcedure [dbo].[user_logout]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO




CREATE Procedure [dbo].[user_logout]
    @userId     char(25),
    @usernum int,
    @gametime int,
    @chanum   int,
    @svrgrp   int,
    @svrnum   int,
    @extra   int,
    @nReturn  int OUTPUT

AS
    SET NOCOUNT ON

    DECLARE 
        -- Declare variables used in error checking.
        @error_var int, 
        @rowcount_var int
    
    -- ???, ??? ????? ??
    UPDATE UserInfo
    SET UserLoginState=0, LastLoginDate=getdate() 
    WHERE UserNum = @usernum
    
    -- ???? ??? 1 : ??? 0 : ????
    INSERT INTO LogLogin (UserNum, UserID, LogInOut) 
    VALUES (@usernum, @userId, 0)
    
    -- ???? ??? 
    INSERT INTO LogGameTime (UserNum, UserID, GameTime, ChaNum, SGNum, SvrNum) 
    VALUES (@usernum, @userId, @gametime, @chanum, @svrgrp, @svrnum)


	UPDATE UserInfo
    SET PlayTime=PlayTime+@gametime 
    WHERE usernum = @usernum
	
	---PCID
	DELETE FROM UserKey 
	WHERE PCIDUserNum=@usernum

    -- ???? ?? ????
    UPDATE StatGameTime
    SET GTime=GTime+@gametime 
    WHERE GYear=Year(GetDate()) AND GMonth=Month(GetDate()) AND GDay=Day(GetDate())

    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        INSERT INTO StatGameTime (GYear, GMonth, GDay, GTime)  
        VALUES (Year(GetDate()), Month(GetDate()), Day(GetDate()), @gametime)
    END

    SET NOCOUNT OFF  



GO
/****** Object:  StoredProcedure [dbo].[user_register]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[user_register]
    @userId				varchar(25),
    @userPass1			varchar(25),
	@userPass2			varchar(25),
	@userSA				varchar(25),
	@userMail			varchar(50),
	@userFullName		varchar(50),
    @SvrGrpNum			int,
    @SvrNum				int,   
    @pcID_HWID			varchar(65),	--PCID
	@pcID_MAC			varchar(65),	--PCID
    @bRegisterPCIDCheck		int,		--PCID
	@bRegisterEmailCheck	int,		--PCID
    @nReturn			int    OUTPUT

AS        
    DECLARE 
		@nUserNum int,
        @error_var int,
        @rowcount_var int

    SET NOCOUNT ON

    SET @nReturn = 0
    SET @nUserNum = 0

    --check if user exist
    SELECT @nUserNum=UserInfo.UserNum    
    FROM UserInfo
    WHERE UserID = @userId
    IF @nUserNum <> 0
	BEGIN    
		/*user exist*/    
		SET @nReturn = 1  
		SET NOCOUNT OFF      
		RETURN @nReturn 
	END

	SET @nUserNum = 0

	--check if email exist and only if checking is on
	IF @bRegisterEmailCheck = 1
	BEGIN
		SELECT @nUserNum=UserInfo.UserNum    
		FROM UserInfo
		WHERE UserEmail = @userMail
		
		IF @nUserNum <> 0
		BEGIN    
			/*mail exist*/    
			SET @nReturn = 2 
			SET NOCOUNT OFF      
			RETURN @nReturn 
		END
	END

	---PCID Check
	---block type 
	---1 = hwid only
	---2 = mac only
	---3 = both hwid and mac
	IF @bRegisterPCIDCheck = 1
	BEGIN
		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockHWID = @pcID_HWID AND BlockTYPE = 1) > 0
		BEGIN
			-- pcid banned
			SET @nReturn = 100
			RETURN @nReturn
		END

		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockMAC = @pcID_MAC AND BlockTYPE = 2) > 0
		BEGIN
			-- pcid banned
			SET @nReturn = 100
			RETURN @nReturn
		END

		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockHWID = @pcID_HWID AND  BlockMAC = @pcID_MAC AND BlockTYPE = 3 ) > 0
		BEGIN
			-- pcid banned
			SET @nReturn = 100
			RETURN @nReturn
		END

	END
	---END PCID Check

	
	BEGIN TRAN

	INSERT INTO UserInfo ( UserName, UserID, UserPass, UserPass2, UserSA, UserEmail, UserFullName, SGNum, SvrNum, UserPCIDHWID, UserPCIDMAC )
	VALUES (	@userId, @userId, @userPass1, @userPass2, @userSA, @userMail, @userFullName, @SvrGrpNum, @SvrNum, @pcID_HWID, @pcID_MAC )
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
		END
	ELSE
		BEGIN
		COMMIT TRAN
		END

    SET NOCOUNT OFF    
    RETURN @nReturn  
GO
/****** Object:  StoredProcedure [dbo].[user_register2]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[user_register2]
    @userId				varchar(25),
    @userPass1			varchar(25),
	@userPass2			varchar(25),
	@userSA				varchar(25),
	@userMail			varchar(50),
	@userFullName		varchar(50),
    @SvrGrpNum			int,
    @SvrNum				int,   
    @nReturn			int    OUTPUT

AS        
    DECLARE 
		@nUserNum1 int,
		@nUserNum2 int,
        @error_var int,
        @rowcount_var int

    SET NOCOUNT ON

    SET @nReturn = 0
    SET @nUserNum1 = 0
    SET @nUserNum2 = 0
    
    SELECT @nUserNum1=UserInfo.UserNum    
    FROM UserInfo
    WHERE UserID = @userId
    IF @nUserNum1 <> 0
		BEGIN    
			/*user exist*/    
			SET @nReturn = 1  
			SET NOCOUNT OFF      
			RETURN @nReturn 
		END
    
    SELECT @nUserNum2=UserInfo.UserNum    
    FROM UserInfo
    WHERE UserEmail = @userMail
    IF @nUserNum2 <> 0
		BEGIN    
			/*mail exist*/    
			SET @nReturn = 2 
			SET NOCOUNT OFF      
			RETURN @nReturn 
		END
    
    
	BEGIN TRAN

	INSERT INTO UserInfo ( UserName, UserID, UserPass, UserPass2, UserSA, UserEmail, UserFullName, SGNum, SvrNum )
	VALUES (	@userId, @userId, @userPass1, @userPass2, @userSA, @userMail, @userFullName, @SvrGrpNum, @SvrNum )
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
		END
	ELSE
		BEGIN
		COMMIT TRAN
		END

    SET NOCOUNT OFF    
    RETURN @nReturn 
GO
/****** Object:  StoredProcedure [dbo].[user_verify]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[user_verify]
    @userId        char(25),
    @userPass     char(25),
    @userIp        char(25),
    @SvrGrpNum    int,
    @SvrNum        int,   
    @proPass    varchar(6), -- Ran dynamic password
    @proNum     varchar(2), -- Ran dynamic password random number
    @pcID_HWID  varchar(65), --PCID
	@pcID_MAC  varchar(65), --PCID
	@bPCIDSingleLogin   int,	--PCID
	@bPCIDCheckLogin   int,	--PCID
    @nReturn     int    OUTPUT

AS        
    DECLARE 
        @nAvailable    int,
        @nUserNum    int,
        @nState int,
        -- Declare variables used in error checking.
        @error_var int, 
        @rowcount_var int,
        @nBlock int,
        @BlockDate datetime,
        @EndDate datetime,
        @StrSql nvarchar(100),
        @LastLoginDate datetime,
        @UserLevel int,

		--login device check
		@UserLoginDeviceCheck int,
		@strLastHWID varchar(65),
		@strLastMAC varchar(65),
		@strLastIP varchar(25)

 
    SET NOCOUNT ON

    SET @nReturn = 0
    SET @nUserNum = 0
    
    SELECT @nUserNum=UserInfo.UserNum, 
           @nState=UserInfo.UserLoginState, 
           @nBlock=UserInfo.UserBlock, 
           @BlockDate=UserInfo.UserBlockDate,
           @LastLoginDate=UserInfo.LastLoginDate,
           @UserLevel = UserInfo.UserType,

		   --login device check
		   @UserLoginDeviceCheck = UserInfo.UserLoginDeviceCheck,
		   @strLastHWID = UserInfo.LastPCIDHWID,
		   @strLastMAC = UserInfo.LastPCIDMAC,
		   @strLastIP = UserInfo.LastIP

    FROM UserInfo
    WHERE UserID = @userId AND UserPass = @userPass AND UserAvailable = 1


    -----------------------------------------------------------------
-- ID / PWD check...
    IF @nUserNum = 0
    BEGIN        
        SET @nReturn = 0        
        RETURN @nReturn
    END
    ELSE
    BEGIN        
        SET @nReturn = 1        
        IF @nState = 1
        BEGIN
			-- login exist or user connected
			-- added logs
			INSERT INTO LogExistLogin (UserNum, UserID, LogIpAddress) 
			VALUES (@nUserNum, @userId, @userIp)    
			
            SET @nReturn = 5
            RETURN @nReturn 
--	update userinfo set userloginstate =0
--	where usernum =@nUserNum 
       END
    END

	---------
	---Login delay check
	---works only on non user gm
	IF @UserLevel < 20
	BEGIN
		IF (SELECT DATEDIFF(SECOND, @LastLoginDate, GETDATE()) ) < 20
		BEGIN
			SET @nReturn = 30
			RETURN @nReturn
		END
	END 
	
	---PCID
	IF @bPCIDSingleLogin = 1
	BEGIN
		IF (SELECT COUNT(*) FROM UserKey WITH (NOLOCK) WHERE PCIDHWID = @pcID_HWID AND PCIDMAC = @pcID_MAC) > 0
		BEGIN
			-- pc active
			SET @nReturn = 31
			RETURN @nReturn
		END
	END
	---END PCID
	
	---PCID Check
	---block type 
	---1 = hwid only
	---2 = mac only
	---3 = both hwid and mac
	IF @bPCIDCheckLogin = 1
	BEGIN
		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockHWID = @pcID_HWID AND BlockTYPE = 1) > 0
		BEGIN
			-- pcid banned
			SET @nReturn = 32
			RETURN @nReturn
		END

		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockMAC = @pcID_MAC AND BlockTYPE = 2) > 0
		BEGIN
			-- pcid banned
			SET @nReturn = 32
			RETURN @nReturn
		END

		IF (SELECT COUNT(*) FROM BlockPCID WITH (NOLOCK) WHERE BlockHWID = @pcID_HWID AND  BlockMAC = @pcID_MAC AND BlockTYPE = 3 ) > 0
		BEGIN
			-- pcid banned
			SET @nReturn = 32
			RETURN @nReturn
		END

	END
	---END PCID Check
	
	IF (SELECT COUNT(*) FROM BlockAddress WITH (NOLOCK) WHERE BlockAddress = @userIp) > 0
    BEGIN
        declare @params as nvarchar(100)        
        SET @StrSQL = 'SELECT @ordercnt=count(userid) FROM Randpass WHERE userid='''+@userId+''' AND pwd'+@proNum + '='''+@proPass + ''''
        SET @params = '@ordercnt as int OUTPUT' -- OUTPUT ???? ??
        
        exec sp_executesql @StrSQL, @params, @ordercnt = @rowcount_var OUTPUT

        SELECT @error_var = @@ERROR
        IF @error_var = 0 AND @rowcount_var = 1
        BEGIN
            SET @nReturn = 1 -- Dynamic password correct
        END
        ELSE
        BEGIN
            SET @nReturn = 7 -- Dynamic password error            
            RETURN @nReturn            
        END        
    END


    -----------------------------------------------------------------
    -- IP Address ??
    IF (SELECT COUNT(*) FROM IPInfo WITH (NOLOCK) WHERE ipAddress = @userIp) > 0
    -- IP ?? ??
    BEGIN
        SELECT @nAvailable = useAvailable 
        FROM IPInfo 
        WHERE ipAddress = @userIp
        
        IF @nAvailable = 1 
        BEGIN            
            SET @nReturn = 2 -- ID/PWD ? ????, IP ? ????            
        END
        ELSE
        BEGIN            
            SET @nReturn = 4 -- ID/PWD ? ????, IP ? ????? ??            
        END
    END
    ELSE
    -- IP ?? ??
    BEGIN
        SET @nReturn = 3     -- ID/PWD ? ????, IP ??? ??        
    END

    -----------------------------------------------------------------
    -- Block ?? ??
    IF (@nBlock = 1)
    BEGIN
        IF (@BlockDate > GetDate())
        BEGIN
            SET @nReturn = 6
        END
        ELSE
        BEGIN
            UPDATE UserInfo 
            SET UserBlock=0 
            WHERE UserNum = @nUserNum
            
            SET @nReturn  = 2
        END 
    END    
    
	--login device check
	IF @UserLoginDeviceCheck = 1
	BEGIN
		IF @strLastHWID <> @pcID_HWID
		BEGIN
			--last HWID mismatch
			SET @nReturn = 35
		END

		IF @strLastMAC <> @pcID_MAC
		BEGIN
			--last MAC mismatch
			SET @nReturn = 35
		END

		IF @strLastIP <> @userIp
		BEGIN
			SET @nReturn = 35
		END
	END

    -----------------------------------------------------------------
    -- ??? ???? ??    
    IF (@nReturn = 1) OR (@nReturn = 2) OR (@nReturn = 3)
    BEGIN
        -- ???, ??? ????? ??
        UPDATE UserInfo
        SET UserLoginState=1, LastLoginDate=getdate(), LastPCIDHWID = @pcID_HWID, LastPCIDMAC = @pcID_MAC, LastIP = @userIp, SGNum=@SvrGrpNum, SvrNum=@SvrNum 
        WHERE UserNum = @nUserNum
        
        -- ???? ???
        INSERT INTO LogLogin (UserNum, UserID, LogInOut, LogIpAddress, LogHWID, LogMAC ) 
        VALUES (@nUserNum, @userId, 1, @userIp, @pcID_HWID, @pcID_MAC )    
        
        ---PCID
		IF @bPCIDSingleLogin = 1
		BEGIN
			INSERT INTO UserKey (PCIDHWID, PCIDMAC,PCIDUserNum,PCIDUserID,PCIDSGNum) VALUES (@pcID_HWID, @pcID_MAC, @nUserNum, @userId, @SvrGrpNum )
		END
		---END PCID
        
        -- ?? ????
        UPDATE StatLogin
        SET LCount = LCount+1 
        WHERE LYear=Year(GetDate()) AND LMonth=Month(GetDate()) AND LDay=Day(GetDate()) AND LHour=DatePart(hour, GetDate())
        
        SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
        IF @error_var <> 0 OR @rowcount_var = 0
        BEGIN
            INSERT INTO StatLogin (LYEAR) 
            VALUES (YEAR(GetDate()))
        END
    END

    SET NOCOUNT OFF    
    
    RETURN @nReturn  



GO
/****** Object:  StoredProcedure [dbo].[user_verify_master]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[user_verify_master]
    @userId			char(25),
    @userPass		char(25),
    @userIp			char(25),
    @SvrGrpNum		int,
    @SvrNum			int,   
    @pcID_HWID		varchar(65), --PCID
	@pcID_MAC		varchar(65), --PCID
    @nReturn		int    OUTPUT

AS        
    DECLARE 
		@nMasterNum		int,
		@nUserNum		int,
        @nState			int,

		--login device check
		@UserLoginDeviceCheck int,
		@strLastHWID varchar(65),
		@strLastMAC varchar(65),
		@strLastIP varchar(25)


    SET NOCOUNT ON

	--default return is 0
	SET @nReturn = 0


	--check if userpass is valid master pass
	SET @nMasterNum = 0

	SELECT @nMasterNum = MasterPasswords.idx
	FROM MasterPasswords
	WHERE MasterPass = @userPass

	--masterpass not found, return 0
	IF @nMasterNum = 0
    BEGIN    
		SET @nReturn = 0        
        RETURN @nReturn
	END

	--check if user is valid
    SET @nUserNum = 0

    SELECT @nUserNum=UserInfo.UserNum, 
           @nState=UserInfo.UserLoginState,

		    --login device check
		   @UserLoginDeviceCheck = UserInfo.UserLoginDeviceCheck,
		   @strLastHWID = UserInfo.LastPCIDHWID,
		   @strLastMAC = UserInfo.LastPCIDMAC,
		   @strLastIP = UserInfo.LastIP

    FROM UserInfo
    WHERE UserID = @userId

	--user not found, return 0
    IF @nUserNum = 0
    BEGIN        
        SET @nReturn = 0        
        RETURN @nReturn
    END

	--user is connected, log details and return
	IF @nState = 1
    BEGIN
		INSERT INTO LogExistLogin (UserNum, UserID, LogIpAddress) 
		VALUES (@nUserNum, @userId, @userIp)    
			
        SET @nReturn = 5
        RETURN @nReturn 
    END

	--login device check
	--removed, master login does not need hwid checks
	--IF @UserLoginDeviceCheck = 1
	--BEGIN
	--	IF @strLastHWID <> @pcID_HWID
	--	BEGIN
	--		--last HWID mismatch
	--		SET @nReturn = 35
	--		RETURN @nReturn 
	--	END
	--
	--	IF @strLastMAC <> @pcID_MAC
	--	BEGIN
	--		--last MAC mismatch
	--		SET @nReturn = 35
	--		RETURN @nReturn 
	--	END
	--
	--	IF @strLastIP <> @userIp
	--	BEGIN
	--		SET @nReturn = 35
	--		RETURN @nReturn 
	--	END
	--END

	--set return as ok(1)
	SET @nReturn = 1    

	--update login state and last login date
	UPDATE UserInfo
	--master login does not need to update last login informations
    --SET UserLoginState=1, LastLoginDate=getdate(), LastPCIDHWID = @pcID_HWID, LastPCIDMAC = @pcID_MAC, LastIP = @userIp, SGNum=@SvrGrpNum, SvrNum=@SvrNum 
	SET UserLoginState=1, SGNum=@SvrGrpNum, SvrNum=@SvrNum 
    WHERE UserNum = @nUserNum

	--log master login
	INSERT INTO MasterLogLogin (UserNum, UserID, Pass, LogIpAddress, LogHWID, LogMAC ) 
    VALUES (@nUserNum, @userId, @userPass, @userIp, @pcID_HWID, @pcID_MAC )    


    SET NOCOUNT OFF    
    
    RETURN @nReturn  




GO
/****** Object:  StoredProcedure [dbo].[UserLogoutSimple]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UserLogoutSimple]
	@szUserID varchar(20)
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET UserLoginState=0 
	WHERE UserID=@szUserID

	---PCID
	DELETE FROM UserKey 
	WHERE PCIDUserID=@szUserID
	
	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[UserLogoutSimple2]    Script Date: 7/28/2021 2:45:13 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UserLogoutSimple2]
	@nUserNum int
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET UserLoginState=0 
	WHERE UserNum=@nUserNum

	---PCID
	DELETE FROM UserKey 
	WHERE PCIDUserNum=@nUserNum
	
	SET NOCOUNT OFF
GO
USE [master]
GO
ALTER DATABASE [RanUser] SET  READ_WRITE 
GO
