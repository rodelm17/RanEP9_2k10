USE [master]
GO
/****** Object:  Database [RanGame1]    Script Date: 1/23/2024 10:57:12 AM ******/
CREATE DATABASE [RanGame1]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'RanGame1P_Data', FILENAME = N'd:\_database_files\RanGame1P_Data.mdf' , SIZE = 8128KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10%), 
 FILEGROUP [SECONDARY] 
( NAME = N'RanGame1S_Data', FILENAME = N'd:\_database_files\RanGame1S_Data.ndf' , SIZE = 8128KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10%)
 LOG ON 
( NAME = N'RanGame1_Log', FILENAME = N'd:\_database_files\RanGame1_Log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [RanGame1] SET COMPATIBILITY_LEVEL = 90
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [RanGame1].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [RanGame1] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [RanGame1] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [RanGame1] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [RanGame1] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [RanGame1] SET ARITHABORT OFF 
GO
ALTER DATABASE [RanGame1] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [RanGame1] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [RanGame1] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [RanGame1] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [RanGame1] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [RanGame1] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [RanGame1] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [RanGame1] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [RanGame1] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [RanGame1] SET  DISABLE_BROKER 
GO
ALTER DATABASE [RanGame1] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [RanGame1] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [RanGame1] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [RanGame1] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [RanGame1] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [RanGame1] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [RanGame1] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [RanGame1] SET RECOVERY FULL 
GO
ALTER DATABASE [RanGame1] SET  MULTI_USER 
GO
ALTER DATABASE [RanGame1] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [RanGame1] SET DB_CHAINING OFF 
GO
ALTER DATABASE [RanGame1] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [RanGame1] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
EXEC sys.sp_db_vardecimal_storage_format N'RanGame1', N'ON'
GO
USE [RanGame1]
GO
/****** Object:  User [user]    Script Date: 1/23/2024 10:57:12 AM ******/
CREATE USER [user] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  Table [dbo].[Attendance]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Attendance](
	[UserNum] [int] NOT NULL,
	[RewardCount] [int] NULL,
	[DaysCount] [int] NULL,
	[AttendDate] [datetime] NULL,
 CONSTRAINT [PK_Attendance] PRIMARY KEY CLUSTERED 
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaAwardTitle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaAwardTitle](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[Title] [varchar](100) NOT NULL,
	[Type] [bigint] NOT NULL,
	[Enabled] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_ChaAwardTitle] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaCombatRecord]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaCombatRecord](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[SGNum] [bigint] NOT NULL,
	[CreatedDate] [datetime] NOT NULL,
	[PVPKills] [bigint] NOT NULL,
	[PVPDeaths] [bigint] NOT NULL,
	[PVPResu] [bigint] NOT NULL,
	[TyrannyKills] [bigint] NOT NULL,
	[TyrannyDeaths] [bigint] NOT NULL,
	[TyrannyResu] [bigint] NOT NULL,
	[ClubWarKills] [bigint] NOT NULL,
	[ClubWarDeaths] [bigint] NOT NULL,
	[ClubWarResu] [bigint] NOT NULL,
	[CaptureTheFlagKills] [bigint] NOT NULL,
	[CaptureTheFlagDeaths] [bigint] NOT NULL,
	[CaptureTheFlagResu] [bigint] NOT NULL,
	[SchoolWarsKills] [bigint] NOT NULL,
	[SchoolWarsDeaths] [bigint] NOT NULL,
	[SchoolWarsResu] [bigint] NOT NULL,
	[ClubDeathMatchKills] [bigint] NOT NULL,
	[ClubDeathMatchDeaths] [bigint] NOT NULL,
	[ClubDeathMatchResu] [bigint] NOT NULL,
	[PKMapKills] [bigint] NOT NULL,
	[PKMapDeaths] [bigint] NOT NULL,
	[PKMapResu] [bigint] NOT NULL,
	[PVEKills] [bigint] NOT NULL,
	[PVEDeaths] [bigint] NOT NULL,
	[PVEMoneyGain] [money] NOT NULL,
 CONSTRAINT [PK_ChaCombatRecord] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaFriend]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaFriend](
	[ChaFriendNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaP] [int] NOT NULL,
	[ChaS] [int] NOT NULL,
	[ChaFlag] [int] NOT NULL,
 CONSTRAINT [PK_ChaFriend] PRIMARY KEY CLUSTERED 
(
	[ChaFriendNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaInfo](
	[ChaNum] [int] IDENTITY(1,1) NOT NULL,
	[SGNum] [int] NULL,
	[UserNum] [int] NOT NULL,
	[GuNum] [int] NULL,
	[GuPosition] [int] NOT NULL,
	[ChaName] [varchar](33) NOT NULL,
	[ChaGuName] [varchar](33) NOT NULL,
	[ChaTribe] [int] NOT NULL,
	[ChaClass] [int] NOT NULL,
	[ChaSchool] [int] NOT NULL,
	[ChaHair] [int] NOT NULL,
	[ChaFace] [int] NOT NULL,
	[ChaLiving] [int] NOT NULL,
	[ChaLevel] [int] NOT NULL,
	[ChaReborn] [int] NOT NULL,
	[ChaMoney] [money] NOT NULL,
	[ChaPower] [bigint] NOT NULL,
	[ChaDex] [bigint] NOT NULL,
	[ChaSpirit] [bigint] NOT NULL,
	[ChaStrong] [bigint] NOT NULL,
	[ChaStrength] [bigint] NOT NULL,
	[ChaIntel] [bigint] NOT NULL,
	[ChaStRemain] [bigint] NOT NULL,
	[ChaExp] [money] NOT NULL,
	[ChaViewRange] [int] NOT NULL,
	[ChaHP] [bigint] NOT NULL,
	[ChaMP] [bigint] NOT NULL,
	[ChaSP] [bigint] NOT NULL,
	[ChaCP] [bigint] NOT NULL,
	[ChaStartMap] [int] NOT NULL,
	[ChaStartGate] [int] NOT NULL,
	[ChaPosX] [float] NOT NULL,
	[ChaPosY] [float] NOT NULL,
	[ChaPosZ] [float] NOT NULL,
	[ChaSaveMap] [int] NOT NULL,
	[ChaSavePosX] [float] NOT NULL,
	[ChaSavePosY] [float] NOT NULL,
	[ChaSavePosZ] [float] NOT NULL,
	[ChaReturnMap] [int] NOT NULL,
	[ChaReturnPosX] [float] NOT NULL,
	[ChaReturnPosY] [float] NOT NULL,
	[ChaReturnPosZ] [float] NOT NULL,
	[ChaBright] [int] NOT NULL,
	[ChaAttackP] [int] NOT NULL,
	[ChaDefenseP] [int] NOT NULL,
	[ChaFightA] [int] NOT NULL,
	[ChaShootA] [int] NOT NULL,
	[ChaPK] [int] NOT NULL,
	[ChaSkillPoint] [int] NOT NULL,
	[ChaInvenLine] [int] NOT NULL,
	[ChaDeleted] [int] NOT NULL,
	[ChaOnline] [int] NOT NULL,
	[ChaCreateDate] [datetime] NOT NULL,
	[ChaDeletedDate] [datetime] NOT NULL,
	[ChaStorage2] [datetime] NOT NULL,
	[ChaStorage3] [datetime] NOT NULL,
	[ChaStorage4] [datetime] NOT NULL,
	[ChaGuSecede] [datetime] NOT NULL,
	[ChaQuest] [image] NULL,
	[ChaSkills] [image] NULL,
	[ChaSkillSlot] [image] NULL,
	[ChaActionSlot] [image] NULL,
	[ChaPutOnItems] [image] NULL,
	[ChaInven] [image] NULL,
	[ChaCoolTime] [image] NULL,
	[ChaSex] [int] NULL,
	[ChaHairStyle] [int] NULL,
	[ChaHairColor] [int] NULL,
	[ChaReExp] [float] NOT NULL,
	[ChaSpSID] [int] NULL,
	[ChaSpMID] [int] NULL,
	[ChaPKRecord] [int] NOT NULL,
	[ChaScaleRange] [float] NOT NULL,
	[ChaItemFood] [image] NULL,
	[ChaDebuff] [image] NULL,
	[ChaContributionPoint] [bigint] NOT NULL,
	[ChaActivity] [image] NULL,
	[ChaBadgeID] [bigint] NOT NULL,
	[ChaActivityPoint] [bigint] NOT NULL,
	[ChaBadge] [varchar](33) NOT NULL,
	[ChaPKScore] [bigint] NOT NULL,
	[ChaPKDeath] [bigint] NOT NULL,
	[ChaEquipmentLockEnable] [bigint] NOT NULL,
	[ChaEquipmentLockStatus] [bigint] NOT NULL,
	[ChaWarChips] [bigint] NOT NULL,
	[ChaGamePoints] [bigint] NOT NULL,
	[ChaPlayTime] [bigint] NOT NULL,
	[ChaPlayPoint] [bigint] NOT NULL,
 CONSTRAINT [PK_ChaInfo] PRIMARY KEY CLUSTERED 
(
	[ChaNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
/****** Object:  Table [dbo].[ChaNameInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaNameInfo](
	[ChaNameNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL,
	[ChaName] [varchar](33) NOT NULL,
 CONSTRAINT [PK_ChaNameInfo] PRIMARY KEY NONCLUSTERED 
(
	[ChaNameNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaPKCombo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaPKCombo](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[SGNum] [bigint] NOT NULL,
	[CreatedDate] [datetime] NOT NULL,
	[PKCombo00] [bigint] NOT NULL,
	[PKCombo01] [bigint] NOT NULL,
	[PKCombo02] [bigint] NOT NULL,
	[PKCombo03] [bigint] NOT NULL,
	[PKCombo04] [bigint] NOT NULL,
	[PKCombo05] [bigint] NOT NULL,
	[PKCombo06] [bigint] NOT NULL,
	[PKCombo07] [bigint] NOT NULL,
 CONSTRAINT [PK_ChaPKCombo] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ChaPKRank]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ChaPKRank](
	[ChaNum] [int] NOT NULL,
	[ChaRank] [bigint] NOT NULL,
 CONSTRAINT [PK_ChaPKRank] PRIMARY KEY CLUSTERED 
(
	[ChaNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GameNotice]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameNotice](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[Message] [varchar](1024) NOT NULL,
	[DaySunday] [int] NOT NULL,
	[DayMonday] [int] NOT NULL,
	[DayTuesday] [int] NOT NULL,
	[DayWednesday] [int] NOT NULL,
	[DayThursday] [int] NOT NULL,
	[DayFriday] [int] NOT NULL,
	[DaySaturday] [int] NOT NULL,
	[Type] [int] NOT NULL,
	[Hour] [int] NOT NULL,
	[Minute] [int] NOT NULL,
 CONSTRAINT [PK_GameNotice] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GuildAlliance]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildAlliance](
	[GuNumP] [int] NOT NULL,
	[GuNumS] [int] NOT NULL,
 CONSTRAINT [PK_GuildAlliance] PRIMARY KEY CLUSTERED 
(
	[GuNumP] ASC,
	[GuNumS] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GuildBattle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildBattle](
	[GuBattleNum] [int] IDENTITY(1,1) NOT NULL,
	[GuSNum] [int] NULL,
	[GuPNum] [int] NULL,
	[GuAlliance] [int] NULL,
	[GuFlag] [int] NULL,
	[GuKillNum] [int] NULL,
	[GuDeathNum] [int] NULL,
	[GuBattleStartDate] [datetime] NULL,
	[GuBattleEndDate] [datetime] NULL,
 CONSTRAINT [PK_GuildBattle] PRIMARY KEY CLUSTERED 
(
	[GuBattleNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GuildInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildInfo](
	[GuNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL,
	[GuDeputy] [int] NOT NULL,
	[GuName] [varchar](33) NOT NULL,
	[GuNotice] [varchar](401) NOT NULL,
	[GuRank] [int] NOT NULL,
	[GuMoney] [money] NOT NULL,
	[GuIncomeMoney] [money] NOT NULL,
	[GuMarkVer] [int] NOT NULL,
	[GuExpire] [int] NOT NULL,
	[GuMakeTime] [datetime] NOT NULL,
	[GuExpireTime] [datetime] NOT NULL,
	[GuAllianceSec] [datetime] NOT NULL,
	[GuAllianceDis] [datetime] NOT NULL,
	[GuMarkImage] [image] NOT NULL,
	[GuStorage] [image] NOT NULL,
	[GuAuthorityTime] [datetime] NOT NULL,
	[GuAllianceBattleLose] [int] NOT NULL,
	[GuAllianceBattleDraw] [int] NOT NULL,
	[GuAllianceBattleWin] [int] NOT NULL,
	[GuBattleLastTime] [datetime] NOT NULL,
	[GuBattleLose] [int] NOT NULL,
	[GuBattleDraw] [int] NOT NULL,
	[GuBattleWin] [int] NOT NULL,
 CONSTRAINT [PK_GuildInfo] PRIMARY KEY CLUSTERED 
(
	[GuNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY],
 CONSTRAINT [IX_GuildInfo_Name] UNIQUE NONCLUSTERED 
(
	[GuName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
/****** Object:  Table [dbo].[GuildRegion]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GuildRegion](
	[RegionID] [int] NOT NULL,
	[GuNum] [int] NOT NULL,
	[RegionTax] [float] NOT NULL,
 CONSTRAINT [PK_GuildRegion] PRIMARY KEY CLUSTERED 
(
	[RegionID] ASC,
	[GuNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogPartyMatch]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogPartyMatch](
	[SGNum] [int] NOT NULL,
	[SvrNum] [int] NOT NULL,
	[Win] [int] NOT NULL,
	[Lost] [int] NOT NULL,
	[MatchTime] [datetime] NOT NULL,
 CONSTRAINT [PK_LogPartyMatch] PRIMARY KEY CLUSTERED 
(
	[MatchTime] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PetInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PetInfo](
	[PetNum] [int] NOT NULL,
	[PetName] [varchar](20) NOT NULL,
	[PetChaNum] [int] NOT NULL,
	[PetType] [int] NOT NULL,
	[PetMID] [int] NOT NULL,
	[PetSID] [int] NOT NULL,
	[PetStyle] [int] NOT NULL,
	[PetColor] [int] NOT NULL,
	[PetFull] [int] NOT NULL,
	[PetDualSkill] [int] NOT NULL,
	[PetDeleted] [int] NOT NULL,
	[PetCreateDate] [datetime] NOT NULL,
	[PetDeletedDate] [datetime] NOT NULL,
	[PetPutOnItems] [image] NOT NULL,
	[PetCardMID] [int] NOT NULL,
	[PetCardSID] [int] NOT NULL,
	[PetUniqueNum] [int] IDENTITY(1,1) NOT NULL,
	[PetSkinStartDate] [datetime] NULL,
	[PetSkinTime] [bigint] NOT NULL,
	[PetSkinScale] [int] NULL,
	[PetSkinMID] [int] NULL,
	[PetSkinSID] [int] NULL,
 CONSTRAINT [PK_PetInfo] PRIMARY KEY CLUSTERED 
(
	[PetUniqueNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
/****** Object:  Table [dbo].[PetInven]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PetInven](
	[PetInvenNum] [int] IDENTITY(1,1) NOT NULL,
	[PetNum] [int] NOT NULL,
	[PetInvenType] [int] NOT NULL,
	[PetInvenMID] [int] NOT NULL,
	[PetInvenSID] [int] NOT NULL,
	[PetInvenCMID] [int] NOT NULL,
	[PetInvenCSID] [int] NOT NULL,
	[PetInvenAvailable] [int] NOT NULL,
	[PetInvenUpdateDate] [datetime] NOT NULL,
	[PetChaNum] [int] NOT NULL,
 CONSTRAINT [PK_PetInven] PRIMARY KEY CLUSTERED 
(
	[PetInvenNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PetStyleFlag]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PetStyleFlag](
	[PetStyle] [int] NOT NULL,
	[PetStyleName] [varchar](2) NOT NULL,
 CONSTRAINT [PK_PetStyleFlag] PRIMARY KEY CLUSTERED 
(
	[PetStyle] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PetTypeFlag]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PetTypeFlag](
	[PetType] [int] NOT NULL,
	[PetName] [varchar](20) NOT NULL,
 CONSTRAINT [PK_PetTypeFlag] PRIMARY KEY CLUSTERED 
(
	[PetType] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PKRecord]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PKRecord](
	[PKRecordNum] [int] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL,
	[ChaKillNum] [int] NOT NULL,
	[ChaKillName] [varchar](33) NOT NULL,
	[ChaPKRecord] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UserInven]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserInven](
	[UserInvenNum] [int] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NOT NULL,
	[SGNum] [int] NOT NULL,
	[ChaStorage2] [datetime] NOT NULL,
	[ChaStorage3] [datetime] NOT NULL,
	[ChaStorage4] [datetime] NOT NULL,
	[UserMoney] [money] NOT NULL,
	[UserInven] [image] NULL,
 CONSTRAINT [IDX_InvenUserNum] PRIMARY KEY CLUSTERED 
(
	[UserInvenNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY],
 CONSTRAINT [IX_UserInven] UNIQUE NONCLUSTERED 
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
/****** Object:  Table [dbo].[UserPersonalLock]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
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
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[VehicleInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[VehicleInfo](
	[VehicleUniqueNum] [int] IDENTITY(1,1) NOT NULL,
	[VehicleNum] [int] NOT NULL,
	[VehicleName] [varchar](20) NOT NULL,
	[VehicleChaNum] [int] NOT NULL,
	[VehicleType] [int] NOT NULL,
	[VehicleCardMID] [int] NOT NULL,
	[VehicleCardSID] [int] NOT NULL,
	[VehicleBattery] [int] NOT NULL,
	[VehicleBooster] [int] NOT NULL,
	[VehicleDeleted] [int] NOT NULL,
	[VehicleCreateDate] [datetime] NOT NULL,
	[VehicleDeletedDate] [datetime] NOT NULL,
	[VehiclePutOnItems] [image] NOT NULL,
	[VehicleColor] [image] NOT NULL,
 CONSTRAINT [PK_VehicleInfo] PRIMARY KEY CLUSTERED 
(
	[VehicleUniqueNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [SECONDARY]
GO
/****** Object:  Table [dbo].[XD_CapTimeLogs]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[XD_CapTimeLogs](
	[capID] [int] IDENTITY(1,1) NOT NULL,
	[UserNum] [int] NULL,
	[ChaNum] [int] NULL,
	[ChaName] [varchar](50) NULL,
	[ChaClass] [int] NULL,
	[ChaLevel] [int] NULL,
	[ChaSchool] [int] NULL,
	[capTime] [datetime] NOT NULL,
 CONSTRAINT [PK_XD_CapTimeLogs] PRIMARY KEY CLUSTERED 
(
	[capID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[XD_ChaRenameLog]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[XD_ChaRenameLog](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ChaNum] [int] NOT NULL,
	[OldName] [varchar](33) NOT NULL,
	[NewName] [varchar](33) NOT NULL,
	[ChangeDate] [datetime] NOT NULL,
 CONSTRAINT [PK_XD_ChaRenameLog] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  View [dbo].[viewChaFriend]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

-------------------------------------------------------------------------------
-- view_ChaFriend
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewChaFriend]
AS
SELECT TOP 100 PERCENT dbo.ChaFriend.ChaP, dbo.ChaFriend.ChaS, 
       dbo.ChaInfo.ChaName, dbo.ChaFriend.ChaFlag
FROM   dbo.ChaFriend INNER JOIN
       dbo.ChaInfo ON dbo.ChaFriend.ChaS = dbo.ChaInfo.ChaNum
ORDER BY dbo.ChaInfo.ChaName

GO
/****** Object:  View [dbo].[viewGuildInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*-----------------------------------------------------------------------------
 view_GuildInfo.sql
-----------------------------------------------------------------------------*/
CREATE VIEW [dbo].[viewGuildInfo]
AS
SELECT     dbo.GuildInfo.GuNum, dbo.GuildInfo.ChaNum, dbo.GuildInfo.GuDeputy, dbo.ChaInfo.ChaName, dbo.GuildInfo.GuName, dbo.GuildInfo.GuNotice, 
                      dbo.GuildInfo.GuRank, dbo.GuildInfo.GuMoney, dbo.GuildInfo.GuIncomeMoney, dbo.GuildInfo.GuMarkVer, dbo.GuildInfo.GuExpire, 
                      dbo.GuildInfo.GuMakeTime, dbo.GuildInfo.GuExpireTime, dbo.GuildInfo.GuAllianceSec, dbo.GuildInfo.GuAllianceDis, dbo.GuildInfo.GuAuthorityTime, 
                      dbo.GuildInfo.GuAllianceBattleLose, dbo.GuildInfo.GuAllianceBattleDraw, dbo.GuildInfo.GuAllianceBattleWin, dbo.GuildInfo.GuBattleLastTime, 
                      dbo.GuildInfo.GuBattleLose, dbo.GuildInfo.GuBattleDraw, dbo.GuildInfo.GuBattleWin, dbo.ChaInfo.ChaSpMID, dbo.ChaInfo.ChaSpSID
FROM         dbo.GuildInfo INNER JOIN
                      dbo.ChaInfo ON dbo.GuildInfo.ChaNum = dbo.ChaInfo.ChaNum
GO
/****** Object:  View [dbo].[viewGuildMember]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

-------------------------------------------------------------------------------
-- view_GuildMember.sql
-------------------------------------------------------------------------------

CREATE VIEW [dbo].[viewGuildMember]
AS
SELECT   dbo.GuildInfo.GuNum, dbo.ChaInfo.ChaNum, dbo.ChaInfo.ChaName, 
         dbo.ChaInfo.ChaGuName, dbo.ChaInfo.GuPosition
FROM     dbo.GuildInfo INNER JOIN
         dbo.ChaInfo ON dbo.GuildInfo.GuNum = dbo.ChaInfo.GuNum
WHERE   (dbo.GuildInfo.GuExpire = 0) AND (dbo.ChaInfo.ChaDeleted = 0)
GO
/****** Object:  Index [IDX_ChaInfoUserNum]    Script Date: 1/23/2024 10:57:12 AM ******/
CREATE NONCLUSTERED INDEX [IDX_ChaInfoUserNum] ON [dbo].[ChaInfo]
(
	[UserNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_ChaInfo]    Script Date: 1/23/2024 10:57:12 AM ******/
CREATE UNIQUE NONCLUSTERED INDEX [IX_ChaInfo] ON [dbo].[ChaInfo]
(
	[ChaName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, FILLFACTOR = 90) ON [PRIMARY]
GO
ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Title]  DEFAULT ('') FOR [Title]
GO
ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Type]  DEFAULT ((0)) FOR [Type]
GO
ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Enabled]  DEFAULT ((0)) FOR [Enabled]
GO
ALTER TABLE [dbo].[ChaAwardTitle] ADD  CONSTRAINT [DF_ChaAwardTitle_Date]  DEFAULT (getdate()) FOR [Date]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CreatedDate]  DEFAULT (getdate()) FOR [CreatedDate]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVPKills]  DEFAULT ((0)) FOR [PVPKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVPDeaths]  DEFAULT ((0)) FOR [PVPDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVPResu]  DEFAULT ((0)) FOR [PVPResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_TyrannyKills]  DEFAULT ((0)) FOR [TyrannyKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_TyrannyDeaths]  DEFAULT ((0)) FOR [TyrannyDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_TyrannyResu]  DEFAULT ((0)) FOR [TyrannyResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubWarKills]  DEFAULT ((0)) FOR [ClubWarKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubWarDeaths]  DEFAULT ((0)) FOR [ClubWarDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubWarResu]  DEFAULT ((0)) FOR [ClubWarResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CaptureTheFlagKills]  DEFAULT ((0)) FOR [CaptureTheFlagKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CaptureTheFlagDeaths]  DEFAULT ((0)) FOR [CaptureTheFlagDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_CaptureTheFlagResu]  DEFAULT ((0)) FOR [CaptureTheFlagResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SchoolWarsKills]  DEFAULT ((0)) FOR [SchoolWarsKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SchoolWarsDeaths]  DEFAULT ((0)) FOR [SchoolWarsDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_SchoolWarsResu]  DEFAULT ((0)) FOR [SchoolWarsResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubDeathMatchKills]  DEFAULT ((0)) FOR [ClubDeathMatchKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubDeathMatchDeaths]  DEFAULT ((0)) FOR [ClubDeathMatchDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_ClubDeathMatchResu]  DEFAULT ((0)) FOR [ClubDeathMatchResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PKMapKills]  DEFAULT ((0)) FOR [PKMapKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PKMapDeaths]  DEFAULT ((0)) FOR [PKMapDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PKMapResu]  DEFAULT ((0)) FOR [PKMapResu]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVEKills]  DEFAULT ((0)) FOR [PVEKills]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVEDeaths]  DEFAULT ((0)) FOR [PVEDeaths]
GO
ALTER TABLE [dbo].[ChaCombatRecord] ADD  CONSTRAINT [DF_ChaCombatRecord_PVEMoneyGain]  DEFAULT ((0)) FOR [PVEMoneyGain]
GO
ALTER TABLE [dbo].[ChaFriend] ADD  CONSTRAINT [DF_ChaFriend_ChaFlag]  DEFAULT ((1)) FOR [ChaFlag]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_GuNum]  DEFAULT ((0)) FOR [GuNum]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_GuPosition]  DEFAULT ((0)) FOR [GuPosition]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaGuName]  DEFAULT ('') FOR [ChaGuName]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaTribe]  DEFAULT ((0)) FOR [ChaTribe]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaClass]  DEFAULT ((0)) FOR [ChaClass]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSchool]  DEFAULT ((0)) FOR [ChaSchool]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaHair]  DEFAULT ((0)) FOR [ChaHair]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaFace]  DEFAULT ((0)) FOR [ChaFace]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaLiving]  DEFAULT ((0)) FOR [ChaLiving]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaLevel]  DEFAULT ((0)) FOR [ChaLevel]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF__ChaInfo__ChaRebo__2EDAF651]  DEFAULT ((0)) FOR [ChaReborn]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaMoney]  DEFAULT ((0)) FOR [ChaMoney]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPower]  DEFAULT ((0)) FOR [ChaPower]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaDex]  DEFAULT ((0)) FOR [ChaDex]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSpirit]  DEFAULT ((0)) FOR [ChaSpirit]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStrong]  DEFAULT ((0)) FOR [ChaStrong]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStrength]  DEFAULT ((0)) FOR [ChaStrength]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaIntel]  DEFAULT ((0)) FOR [ChaIntel]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStRemain]  DEFAULT ((0)) FOR [ChaStRemain]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaExp]  DEFAULT ((0)) FOR [ChaExp]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaViewRange]  DEFAULT ((0)) FOR [ChaViewRange]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaHP]  DEFAULT ((0)) FOR [ChaHP]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaMP]  DEFAULT ((0)) FOR [ChaMP]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSP]  DEFAULT ((0)) FOR [ChaSP]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaCP]  DEFAULT ((0)) FOR [ChaCP]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStartMap]  DEFAULT ((0)) FOR [ChaStartMap]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStartGate]  DEFAULT ((0)) FOR [ChaStartGate]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPosX]  DEFAULT ((0)) FOR [ChaPosX]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPosY]  DEFAULT ((0)) FOR [ChaPosY]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPosZ]  DEFAULT ((0)) FOR [ChaPosZ]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSaveMap]  DEFAULT ((-1)) FOR [ChaSaveMap]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSavePosX]  DEFAULT ((0)) FOR [ChaSavePosX]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSavePosY]  DEFAULT ((0)) FOR [ChaSavePosY]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSavePosZ]  DEFAULT ((0)) FOR [ChaSavePosZ]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaReturnMap]  DEFAULT ((-1)) FOR [ChaReturnMap]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaReturnPosX]  DEFAULT ((0)) FOR [ChaReturnPosX]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaReturnPosY]  DEFAULT ((0)) FOR [ChaReturnPosY]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaReturnPosZ]  DEFAULT ((0)) FOR [ChaReturnPosZ]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaBright]  DEFAULT ((0)) FOR [ChaBright]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaAttackP]  DEFAULT ((0)) FOR [ChaAttackP]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaDefenseP]  DEFAULT ((0)) FOR [ChaDefenseP]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaFightA]  DEFAULT ((0)) FOR [ChaFightA]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaShootA]  DEFAULT ((0)) FOR [ChaShootA]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPK]  DEFAULT ((0)) FOR [ChaPK]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSkillPoint]  DEFAULT ((0)) FOR [ChaSkillPoint]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaInvenLine]  DEFAULT ((0)) FOR [ChaInvenLine]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaDeleted]  DEFAULT ((0)) FOR [ChaDeleted]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaOnline]  DEFAULT ((0)) FOR [ChaOnline]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaCreateDate]  DEFAULT (getdate()) FOR [ChaCreateDate]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaDeletedDate]  DEFAULT (getdate()) FOR [ChaDeletedDate]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStorage2]  DEFAULT ('1970-02-01') FOR [ChaStorage2]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStorage3]  DEFAULT ('1970-02-01') FOR [ChaStorage3]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaStorage4]  DEFAULT ('1970-02-01') FOR [ChaStorage4]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaGuSecede]  DEFAULT ('1970-02-01') FOR [ChaGuSecede]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaReExp]  DEFAULT ((0)) FOR [ChaReExp]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSpSID_1]  DEFAULT ((0)) FOR [ChaSpSID]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaSpMID_1]  DEFAULT ((0)) FOR [ChaSpMID]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPKRecord]  DEFAULT ((0)) FOR [ChaPKRecord]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaScaleRange]  DEFAULT ((1)) FOR [ChaScaleRange]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaContributionPoint_1]  DEFAULT ((0)) FOR [ChaContributionPoint]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaBadgeID]  DEFAULT ((0)) FOR [ChaBadgeID]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaActivityPoint]  DEFAULT ((0)) FOR [ChaActivityPoint]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaBadge]  DEFAULT ('') FOR [ChaBadge]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPKScore]  DEFAULT ((0)) FOR [ChaPKScore]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPKDeath]  DEFAULT ((0)) FOR [ChaPKDeath]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPutOnKey]  DEFAULT ((0)) FOR [ChaEquipmentLockEnable]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPutOnLock]  DEFAULT ((0)) FOR [ChaEquipmentLockStatus]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaWarChips]  DEFAULT ((0)) FOR [ChaWarChips]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaGamePoints]  DEFAULT ((0)) FOR [ChaGamePoints]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPlayTime]  DEFAULT ((0)) FOR [ChaPlayTime]
GO
ALTER TABLE [dbo].[ChaInfo] ADD  CONSTRAINT [DF_ChaInfo_ChaPlayPoint]  DEFAULT ((0)) FOR [ChaPlayPoint]
GO
ALTER TABLE [dbo].[ChaNameInfo] ADD  CONSTRAINT [DF_ChaNameInfo_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[ChaNameInfo] ADD  CONSTRAINT [DF_ChaNameInfo_ChaName]  DEFAULT ('') FOR [ChaName]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_CreatedDate]  DEFAULT (getdate()) FOR [CreatedDate]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo00]  DEFAULT ((0)) FOR [PKCombo00]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo01]  DEFAULT ((0)) FOR [PKCombo01]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo02]  DEFAULT ((0)) FOR [PKCombo02]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo03]  DEFAULT ((0)) FOR [PKCombo03]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo04]  DEFAULT ((0)) FOR [PKCombo04]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo05]  DEFAULT ((0)) FOR [PKCombo05]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo06]  DEFAULT ((0)) FOR [PKCombo06]
GO
ALTER TABLE [dbo].[ChaPKCombo] ADD  CONSTRAINT [DF_ChaPKCombo_PKCombo07]  DEFAULT ((0)) FOR [PKCombo07]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_Table_1_NoticeMessage]  DEFAULT ('') FOR [Message]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DaySunday]  DEFAULT ((0)) FOR [DaySunday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayMonday]  DEFAULT ((0)) FOR [DayMonday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_Table_1_DayTuesDay]  DEFAULT ((0)) FOR [DayTuesday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayWednesday]  DEFAULT ((0)) FOR [DayWednesday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayThursday]  DEFAULT ((0)) FOR [DayThursday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DayFriday]  DEFAULT ((0)) FOR [DayFriday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_DaySaturday]  DEFAULT ((0)) FOR [DaySaturday]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_Type]  DEFAULT ((0)) FOR [Type]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_Hour]  DEFAULT ((0)) FOR [Hour]
GO
ALTER TABLE [dbo].[GameNotice] ADD  CONSTRAINT [DF_GameNotice_Minute]  DEFAULT ((0)) FOR [Minute]
GO
ALTER TABLE [dbo].[GuildAlliance] ADD  CONSTRAINT [DF_GuildAlliance_GuNumP]  DEFAULT ((0)) FOR [GuNumP]
GO
ALTER TABLE [dbo].[GuildAlliance] ADD  CONSTRAINT [DF_GuildAlliance_GuNumS]  DEFAULT ((0)) FOR [GuNumS]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuSNum]  DEFAULT ((0)) FOR [GuSNum]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuPNum]  DEFAULT ((0)) FOR [GuPNum]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuAlliance]  DEFAULT ((0)) FOR [GuAlliance]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuFlag]  DEFAULT ((0)) FOR [GuFlag]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuKillNum]  DEFAULT ((0)) FOR [GuKillNum]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuBattleStartDate]  DEFAULT (getdate()) FOR [GuBattleStartDate]
GO
ALTER TABLE [dbo].[GuildBattle] ADD  CONSTRAINT [DF_GuildBattle_GuBattleEndDate]  DEFAULT (getdate()) FOR [GuBattleEndDate]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuDeputy]  DEFAULT ((0)) FOR [GuDeputy]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuName]  DEFAULT ('') FOR [GuName]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuNotice]  DEFAULT ('') FOR [GuNotice]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuRank]  DEFAULT ((0)) FOR [GuRank]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuMoney]  DEFAULT ((0)) FOR [GuMoney]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuIncomeMoney]  DEFAULT ((0)) FOR [GuIncomeMoney]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuMarkVer]  DEFAULT ((0)) FOR [GuMarkVer]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuExpire]  DEFAULT ((0)) FOR [GuExpire]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuMakeTime]  DEFAULT (getdate()) FOR [GuMakeTime]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuExpireTime]  DEFAULT ('1970-02-01') FOR [GuExpireTime]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuAllianceSec]  DEFAULT ('1970-02-01') FOR [GuAllianceSec]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuAllianceDis]  DEFAULT ('1970-02-01') FOR [GuAllianceDis]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuMarkImage]  DEFAULT ('') FOR [GuMarkImage]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuStorage]  DEFAULT ('') FOR [GuStorage]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuAuthorityTime_1]  DEFAULT ('1970-02-01') FOR [GuAuthorityTime]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuAllianceBattleLose_1]  DEFAULT ((0)) FOR [GuAllianceBattleLose]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuAllianceBattleDraw_1]  DEFAULT ((0)) FOR [GuAllianceBattleDraw]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuAllianceBattleWin_1]  DEFAULT ((0)) FOR [GuAllianceBattleWin]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuBattleLastTime_1]  DEFAULT ('1970-02-01') FOR [GuBattleLastTime]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuBattleLose_1]  DEFAULT ((0)) FOR [GuBattleLose]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuBattleDraw_1]  DEFAULT ((0)) FOR [GuBattleDraw]
GO
ALTER TABLE [dbo].[GuildInfo] ADD  CONSTRAINT [DF_GuildInfo_GuBattleWin_1]  DEFAULT ((0)) FOR [GuBattleWin]
GO
ALTER TABLE [dbo].[GuildRegion] ADD  CONSTRAINT [DF_GuildRegion_GuNum]  DEFAULT ((0)) FOR [GuNum]
GO
ALTER TABLE [dbo].[GuildRegion] ADD  CONSTRAINT [DF_GuildRegion_RegionTax]  DEFAULT ((0.0)) FOR [RegionTax]
GO
ALTER TABLE [dbo].[LogPartyMatch] ADD  CONSTRAINT [DF_LogPartyMatch_SGNum]  DEFAULT ((0)) FOR [SGNum]
GO
ALTER TABLE [dbo].[LogPartyMatch] ADD  CONSTRAINT [DF_LogPartyMatch_SvrNum]  DEFAULT ((0)) FOR [SvrNum]
GO
ALTER TABLE [dbo].[LogPartyMatch] ADD  CONSTRAINT [DF_LogPartyMatch_Win]  DEFAULT ((0)) FOR [Win]
GO
ALTER TABLE [dbo].[LogPartyMatch] ADD  CONSTRAINT [DF_LogPartyMatch_Lost]  DEFAULT ((0)) FOR [Lost]
GO
ALTER TABLE [dbo].[LogPartyMatch] ADD  CONSTRAINT [DF_LogPartyMatch_MatchTime]  DEFAULT (getdate()) FOR [MatchTime]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetNum]  DEFAULT ((0)) FOR [PetNum]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetName]  DEFAULT ('') FOR [PetName]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetChaNum]  DEFAULT ((0)) FOR [PetChaNum]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetType]  DEFAULT ((0)) FOR [PetType]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetMID]  DEFAULT ((0)) FOR [PetMID]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetSID]  DEFAULT ((0)) FOR [PetSID]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetStyle]  DEFAULT ((0)) FOR [PetStyle]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetColor]  DEFAULT ((0)) FOR [PetColor]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetFull]  DEFAULT ((1000)) FOR [PetFull]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetDualSkill]  DEFAULT ((0)) FOR [PetDualSkill]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetDeleted]  DEFAULT ((0)) FOR [PetDeleted]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetCreateDate]  DEFAULT (getdate()) FOR [PetCreateDate]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetDeletedDate]  DEFAULT (getdate()) FOR [PetDeletedDate]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetPutOnItems]  DEFAULT ('') FOR [PetPutOnItems]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetCardMID]  DEFAULT ((0)) FOR [PetCardMID]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetCardSID]  DEFAULT ((0)) FOR [PetCardSID]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetSkinStartDate]  DEFAULT (getdate()) FOR [PetSkinStartDate]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetSkinTime]  DEFAULT ((0)) FOR [PetSkinTime]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetSkinScale]  DEFAULT ((0)) FOR [PetSkinScale]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetSkinMID]  DEFAULT ((0)) FOR [PetSkinMID]
GO
ALTER TABLE [dbo].[PetInfo] ADD  CONSTRAINT [DF_PetInfo_PetSkinSID]  DEFAULT ((0)) FOR [PetSkinSID]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetNum]  DEFAULT ((0)) FOR [PetNum]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenType]  DEFAULT ((0)) FOR [PetInvenType]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenMID]  DEFAULT ((0)) FOR [PetInvenMID]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenSID]  DEFAULT ((0)) FOR [PetInvenSID]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenCMID]  DEFAULT ((0)) FOR [PetInvenCMID]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenCSID]  DEFAULT ((0)) FOR [PetInvenCSID]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenAvailable]  DEFAULT ((0)) FOR [PetInvenAvailable]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetInvenUpdateDate]  DEFAULT (getdate()) FOR [PetInvenUpdateDate]
GO
ALTER TABLE [dbo].[PetInven] ADD  CONSTRAINT [DF_PetInven_PetChaNum]  DEFAULT ('0') FOR [PetChaNum]
GO
ALTER TABLE [dbo].[PKRecord] ADD  CONSTRAINT [DF_PKRecord_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO
ALTER TABLE [dbo].[UserInven] ADD  CONSTRAINT [DF_UserInven_ChaStorage2]  DEFAULT ('1970-02-01') FOR [ChaStorage2]
GO
ALTER TABLE [dbo].[UserInven] ADD  CONSTRAINT [DF_UserInven_ChaStorage3]  DEFAULT ('1970-02-01') FOR [ChaStorage3]
GO
ALTER TABLE [dbo].[UserInven] ADD  CONSTRAINT [DF_UserInven_ChaStorage4]  DEFAULT ('1970-02-01') FOR [ChaStorage4]
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
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleNum]  DEFAULT ((0)) FOR [VehicleNum]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleName]  DEFAULT ('') FOR [VehicleName]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleChaNum]  DEFAULT ((0)) FOR [VehicleChaNum]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleType]  DEFAULT ((0)) FOR [VehicleType]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleCardMID]  DEFAULT ((0)) FOR [VehicleCardMID]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleCardSID]  DEFAULT ((0)) FOR [VehicleCardSID]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleBattery]  DEFAULT ((1000)) FOR [VehicleBattery]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleBooster]  DEFAULT ((0)) FOR [VehicleBooster]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleDeleted]  DEFAULT ((0)) FOR [VehicleDeleted]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleCreateDate]  DEFAULT (getdate()) FOR [VehicleCreateDate]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleDeletedDate]  DEFAULT (getdate()) FOR [VehicleDeletedDate]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehiclePutOnItems]  DEFAULT ('') FOR [VehiclePutOnItems]
GO
ALTER TABLE [dbo].[VehicleInfo] ADD  CONSTRAINT [DF_VehicleInfo_VehicleColor]  DEFAULT ('') FOR [VehicleColor]
GO
ALTER TABLE [dbo].[XD_ChaRenameLog]  WITH CHECK ADD  CONSTRAINT [FK_XD_ChaRenameLog_ChaInfo] FOREIGN KEY([ChaNum])
REFERENCES [dbo].[ChaInfo] ([ChaNum])
GO
ALTER TABLE [dbo].[XD_ChaRenameLog] CHECK CONSTRAINT [FK_XD_ChaRenameLog_ChaInfo]
GO
ALTER TABLE [dbo].[XD_ChaRenameLog]  WITH CHECK ADD  CONSTRAINT [CK_XD_ChaRenameLog_name_differs] CHECK  (([OldName]<>[NewName]))
GO
ALTER TABLE [dbo].[XD_ChaRenameLog] CHECK CONSTRAINT [CK_XD_ChaRenameLog_name_differs]
GO
/****** Object:  StoredProcedure [dbo].[DeleteChaFriend]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[DeleteChaFriend]
	@nChaP int,
	@nChaS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	DELETE FROM ChaFriend 
	WHERE ChaP=@nChaP AND ChaS=@nChaS	
    
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
/****** Object:  StoredProcedure [dbo].[DeleteGuildAlliance]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[DeleteGuildAlliance]
	@nGuNumP int,
	@nGuNumS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	DELETE GuildAlliance 
	WHERE GuNumP=@nGuNumP AND GuNumS=@nGuNumS
	
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
/****** Object:  StoredProcedure [dbo].[GetInvenCount]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[GetInvenCount]    
    @nUserNum int,
	@nReturn int OUTPUT
AS		
	SET NOCOUNT ON
	
	SET @nReturn = 0		

	IF EXISTS (SELECT UserInvenNum FROM UserInven WHERE UserNum=@nUserNum) 
	BEGIN
		SET @nReturn = 1
	END
	ELSE
	BEGIN
        SET @nReturn = 0
	END
	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[InsertChaFriend]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[InsertChaFriend]
	@nChaP int,
	@nChaS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO ChaFriend (ChaP, ChaS) 
	VALUES(@nChaP, @nChaS)
    
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
/****** Object:  StoredProcedure [dbo].[InsertGuildAlliance]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[InsertGuildAlliance]
	@nGuNump int,
	@nGuNumS int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    INSERT INTO GuildAlliance (GuNumP, GuNumS) 
    VALUES (@nGuNump, @nGuNumS)
    
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
/****** Object:  StoredProcedure [dbo].[InsertPartyMatch]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[InsertPartyMatch]
	@nSGNum  int,
	@nSvrNum int,
    @nWin    int,
	@nLost   int
AS
	SET NOCOUNT ON

	INSERT INTO LogPartyMatch (SGNum, SvrNum, Win, Lost) 
	VALUES (@nSGNum, @nSvrNum, @nWin, @nLost)

	SET NOCOUNT OFF
GO
/****** Object:  StoredProcedure [dbo].[MakeUserInven]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[MakeUserInven]
    @nSGNum int,
    @nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO UserInven (SGNum, UserNum, UserMoney, UserInven) 
	VALUES(@nSGNum, @nUserNum, 0,'')	
	
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
/****** Object:  StoredProcedure [dbo].[PersonalLockCheck]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[PersonalLockCheck]    
    @nUserNum int,
	@nReturn int OUTPUT
AS		
	SET NOCOUNT ON
	
	SET @nReturn = 0		

	IF EXISTS (SELECT Num FROM UserPersonalLock WHERE UserNum=@nUserNum) 
	BEGIN
		SET @nReturn = 1
	END
	ELSE
	BEGIN
        SET @nReturn = 0
	END
	SET NOCOUNT OFF

	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[PersonalLockMake]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[PersonalLockMake]
    @nSGNum int,
    @nUserNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO UserPersonalLock (SGNum, UserNum, UserLockPuton, UserLockInven, UserLockLocker, UserPinPuton, UserPinInven, UserPinLocker ) 
	VALUES(@nSGNum, @nUserNum, 0, 0, 0,'','','')	
	
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
/****** Object:  StoredProcedure [dbo].[PKComboCheck]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[PKComboCheck]    
    @nChaNum int,
	@nReturn int OUTPUT
AS		
	SET NOCOUNT ON
	
	SET @nReturn = 0		

	IF EXISTS (SELECT idx FROM ChaPKCombo WHERE ChaNum=@nChaNum) 
	BEGIN
		SET @nReturn = 1
	END
	ELSE
	BEGIN
        SET @nReturn = 0
	END
	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[PKComboMake]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[PKComboMake]
    @nSGNum int,
    @nChaNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO ChaPKCombo(ChaNum, SGNum, CreatedDate, PKCombo00, PKCombo01, PKCombo02, PKCombo03, PKCombo04, PKCombo05, PKCombo06, PKCombo07 ) 
	VALUES(@nChaNum, @nSGNum, GETDATE(), 0, 0, 0, 0, 0, 0, 0, 0)	
	
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
/****** Object:  StoredProcedure [dbo].[RenameCharacter]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[RenameCharacter]
	@nChaNum int,
	@szChaName varchar(33),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0
	
	SELECT @nChaNumTemp=ChaNum FROM ChaInfo WHERE ChaName=@szChaName
	
	IF @nChaNumTemp <> 0 -- ???? ?? ??
	BEGIN
		SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END
	
    UPDATE ChaInfo
    SET ChaName=@szChaName
    WHERE ChaNum=@nChaNum
	/*
	UPDATE ChaEquipmentPass
	SET ChaName=@szChaName
    WHERE ChaNum=@nChaNum
    */
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
/****** Object:  StoredProcedure [dbo].[sp_add_guild_member]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_add_guild_member]
    @GuNum int,
    @ChaNum int,
	@nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int, -- ?? ??         
         @error_var int, 
		 @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    -----------------------------------------------------------------
    -- Character ? ?? ????? ?????.
    UPDATE ChaInfo 
    SET GuNum=@GuNum 
    WHERE ChaNum=@ChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
    -- ??? ???? ?? ????
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN    
        SET @nReturn = 1
        -- ??? ????.
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_add_guild_region]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE Procedure [dbo].[sp_add_guild_region]
	@RegionID int,
    @GuNum    int,
    @RegionTax float,
	@nReturn int	OUTPUT	
AS
	DECLARE @error_var int, 
		    @rowcount_var int
		    
	SET NOCOUNT ON
		 
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0
	
	IF EXISTS(SELECT * FROM GuildRegion WHERE RegionID=@RegionID)
	BEGIN -- ??? ????
		UPDATE GuildRegion 
		SET GuNum=@GuNum, RegionTax=@RegionTax 
		WHERE RegionID=@RegionID
		
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
		IF @error_var <> 0 OR @rowcount_var = 0 -- ????
		BEGIN
			SET @nReturn = 0
			SET NOCOUNT OFF
			RETURN @nReturn
		END
	END
	ELSE
	BEGIN
		INSERT INTO GuildRegion (RegionID, GuNum, RegionTax) 
		VALUES (@RegionID, @GuNum, @RegionTax)
		
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
		IF @error_var <> 0 OR @rowcount_var = 0 -- ????
		BEGIN
			SET @nReturn = 0
			SET NOCOUNT OFF
			RETURN @nReturn
		END
	END
	SET @nReturn = 1
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_ChangeEquipmentPass]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_ChangeEquipmentPass]
	@nChaNum int,
	@szChaEPass varchar(4),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nNum int,
		@nCharNum int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nNum = 0
	SET @nCharNum = 0

	SELECT @nNum=ChaEquipmentPass.Num    
    FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum

    IF @nNum = 0
    BEGIN    
		 --data not exist
        SET @nReturn = 1   
        SET NOCOUNT OFF    
        RETURN @nReturn 
    END
    
	--update epass
    UPDATE ChaEquipmentPass
    SET ChaEPass=@szChaEPass
    WHERE ChaNum=@nChaNum

    
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
/****** Object:  StoredProcedure [dbo].[sp_CheckEquipmentPass]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_CheckEquipmentPass]
	@nChaNum int,
	@szChaEPass varchar(4),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nNum int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nNum = 0

	SELECT @nNum=ChaEquipmentPass.Num    
    FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum AND ChaEPass = @szChaEPass

    IF @nNum > 0
    BEGIN
		--found
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn  
    END
    ELSE
    BEGIN
		--not found
        SET @nReturn = 1  
        SET NOCOUNT OFF     
        RETURN @nReturn 
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_CombatRecordCheck]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_CombatRecordCheck]    
    @nChaNum int,
	@nReturn int OUTPUT
AS		
	SET NOCOUNT ON
	
	SET @nReturn = 0		

	IF EXISTS (SELECT idx FROM ChaCombatRecord WHERE ChaNum=@nChaNum) 
	BEGIN
		SET @nReturn = 1
	END
	ELSE
	BEGIN
        SET @nReturn = 0
	END
	SET NOCOUNT OFF

	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_CombatRecordMake]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_CombatRecordMake]
    @nSGNum int,
    @nChaNum int,
	@nPKScorePREV int,
	@nPKDeathPREV int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	INSERT INTO ChaCombatRecord(ChaNum, SGNum, CreatedDate, PVPKills, PVPDeaths ) 
	VALUES(@nChaNum, @nSGNum, GETDATE(), @nPKScorePREV, @nPKDeathPREV )	
	
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
/****** Object:  StoredProcedure [dbo].[sp_create_guild]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_create_guild]
    @ChaNum  int,
	@GuName  char(33),
	@nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int, -- ?? ??         
         @error_var int, 
		 @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    -----------------------------------------------------------------
    -- ?? ?? ???? ???? ??? ????.  
	SELECT @nGuNum=GuNum 
	FROM GuildInfo 
	WHERE ChaNum=@ChaNum
      
	IF @nGuNum <> 0 -- ??? ??, ???????
	BEGIN 
		SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	
	-----------------------------------------------------------------
    -- ??? ??? ????.
    INSERT INTO GuildInfo (ChaNum, GuName) 
    VALUES (@ChaNum, @GuName)
    
    SELECT @error_var = @@ERROR
    IF @error_var <> 0 
    BEGIN
        -- ?? ??? ????
        SET @nReturn = -2
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    
    -----------------------------------------------------------------
    -- ??? ?? ????, ????? ????. 
    SELECT @nGuNum=@@IDENTITY
    
    SET @nReturn = @nGuNum
    
    -----------------------------------------------------------------
    -- ??? ??? ???(Guild Master)? ?????? ????? ????.
    UPDATE ChaInfo 
    SET GuNum=@nGuNum 
    WHERE ChaNum=@ChaNum
    
    -- ??? ????? ????.
    SET NOCOUNT OFF
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_character]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[sp_delete_character]
	@ChaNum  int,
	@nReturn int OUTPUT
AS    
    DECLARE
	@nGuNum int, -- ?? ??    
	@error_var int, 
	@rowcount_var int,
	@nChaDeleted int,
	@nExtreme int


	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	SET @nChaDeleted = 0
	SET @nExtreme = 0
	
	-----------------------------------------------------------------
	-- ?? ???? ?????? ????.
	SELECT @nChaDeleted=ChaDeleted FROM ChaInfo WHERE ChaNum=@ChaNum
	IF @nChaDeleted = 1
	BEGIN	
		SET @nReturn = -1
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	
	-----------------------------------------------------------------
    -- ?? ?? ???? ???? ??? ????.  
	SELECT @nGuNum=GuNum FROM GuildInfo WHERE ChaNum=@ChaNum
      
	IF @nGuNum <> 0 -- ??? ??, ??????? ??? ???? ??/?? ????? ???? ??.
	BEGIN 
		SET @nReturn = -2
		SET NOCOUNT OFF
		RETURN @nReturn
	END

	-----------------------------------------------------------------
	-- ??? ???? ????? ????.
	SELECT @nExtreme=ChaClass From ChaInfo Where ChaNum=@ChaNum
	
	-----------------------------------------------------------------
	-- ???? ????.
	UPDATE ChaInfo SET ChaDeleted=1 , ChaDeletedDate=getdate() WHERE ChaNum=@ChaNum
    
	IF @nExtreme=16
	BEGIN
		SET @nReturn = 1 -- ??? ??? ?????.
	END
	ELSE IF @nExtreme=32
	BEGIN
		SET @nReturn=2 -- ??? ??? ?????.
	END
	ELSE
	BEGIN
		SET @nReturn=0
	END
    
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_guild]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_delete_guild]    
    @GuNum int,
    @ChaNum  int,	
	@nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int, -- ?? ??         
         @error_var int, 
		 @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    -----------------------------------------------------------------
    -- ????? ????.
    DELETE GuildInfo 
    WHERE GuNum=@GuNum AND ChaNum=@ChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
    -- ??? ???? ?? ????
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END    
    
    -----------------------------------------------------------------
    -- ??? ???? ?? ???? ????? 0 ?? ????.
    UPDATE ChaInfo 
    SET GuNum=0, GuPosition=0 
    WHERE GuNum=@GuNum
    
    -----------------------------------------------------------------
    -- ?? ???? ??? ????.
    DELETE GuildAlliance 
    WHERE GuNumP=@GuNum OR GuNumS=@GuNum
    
    SET @nReturn = 1
    
    -- ??? ????.
    SET NOCOUNT OFF
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_guild_member]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_delete_guild_member]
    @ChaNum int,
    @nReturn int	OUTPUT
AS    
    DECLARE @nGuNum int,
         @error_var int, 
         @rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET	@nGuNum = 0
	SET @error_var = 0
	SET @rowcount_var = 0
	
    UPDATE ChaInfo 
    SET GuNum=0, GuPosition=0, ChaGuSecede=getdate()
    WHERE ChaNum=@ChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN    
        SET @nReturn = 1        
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_delete_guild_region]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE Procedure [dbo].[sp_delete_guild_region]
	@RegionID int,
    @GuNum int,
	@nReturn int	OUTPUT	
AS
	DECLARE @error_var int, 
		    @rowcount_var int

	SET NOCOUNT ON
		 
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0
	
	IF EXISTS(SELECT * FROM GuildRegion WHERE RegionID=@RegionID AND GuNum=@GuNum)
	BEGIN -- ??? ??? ????
		UPDATE GuildRegion 
		SET GuNum=0, RegionTax=0 
		WHERE RegionID=@RegionID
		
		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
		IF @error_var <> 0 OR @rowcount_var = 0 -- ????
		BEGIN
			SET @nReturn = 0
			SET NOCOUNT OFF
			RETURN @nReturn
		END
	END
	ELSE -- ??? ??? ???? ??? ??
	BEGIN
		SET @nReturn = 0
		SET NOCOUNT OFF			
		RETURN @nReturn		
	END
	
	SET @nReturn = 1
	SET NOCOUNT OFF
	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_DeleteEquipmentPass]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_DeleteEquipmentPass]
	@nChaNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nNum int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nNum = 0

	SELECT @nNum=ChaEquipmentPass.Num    
    FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum

    IF @nNum = 0
    BEGIN    
		 --data not exist
        SET @nReturn = -1   
        SET NOCOUNT OFF    
        RETURN @nReturn 
    END
    
    -- delete entry
    DELETE FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum
    
    -- remove charinfo locks
    UPDATE ChaInfo 
    SET ChaEquipmentLockEnable = 0, ChaEquipmentLockStatus = 0 
    WHERE ChaNum=@nChaNum 
        
    SET @nReturn = 0
    SET NOCOUNT OFF
    RETURN @nReturn 
GO
/****** Object:  StoredProcedure [dbo].[sp_DeletePet]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[sp_DeletePet]
	@nChaNum	int,
	@nPetNum	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetDeleted=1, PetDeletedDate=getdate()
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_DeleteVehicle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_DeleteVehicle]
	@nVehicleNum	int,
	@nVehicleChaNum int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE VehicleInfo
	SET VehicleDeleted=1, VehicleDeletedDate=getdate()
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum=@nVehicleChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_EndGuAllianceBattle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_EndGuAllianceBattle]
    @nClubP  int,
    @nClubS  int,
	@nGuFlag int,
	@nGuKillNum int, 
	@nGuDeathNum int,
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    BEGIN TRAN

	UPDATE GuildBattle
	SET GuFlag=@nGuFlag, GuKillNum=@nGuKillNum, GuDeathNum=@nGuDeathNum
	WHERE GuSNum=@nClubS AND GuPNum=@nClubP AND GuFlag=0 AND GuAlliance=1

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	-- CLUB_BATTLE_DRAW, CLUB_BATTLE_ARMISTICE
	IF (@nGuFlag = 1) OR (@nGuFlag = 2)  
	BEGIN
		UPDATE GuildInfo
        SET GuAllianceBattleDraw=GuAllianceBattleDraw+1
        WHERE GuNum = @nClubP
	END

	-- CLUB_BATTLE_LOSE, CLUB_BATTLE_SUBMISSION
	IF (@nGuFlag = 5 ) OR (@nGuFlag = 3)
	BEGIN
		UPDATE GuildInfo
        SET GuAllianceBattleLose=GuAllianceBattleLose+1
        WHERE GuNum = @nClubP
	END

	-- CLUB_BATTLE_WIN, CLUB_BATTLE_SUBMISSION_WIN
	IF (@nGuFlag = 6 ) OR (@nGuFlag = 4)
	BEGIN
		UPDATE GuildInfo
        SET GuAllianceBattleWin=GuAllianceBattleWin+1
        WHERE GuNum = @nClubP
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_EndGuBattle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_EndGuBattle]
    @nClubP  int,
    @nClubS  int,
	@nGuFlag int,
	@nGuKillNum int, 
	@nGuDeathNum int,
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    BEGIN TRAN

	UPDATE GuildBattle
	SET GuFlag=@nGuFlag, GuKillNum=@nGuKillNum, GuDeathNum=@nGuDeathNum
	WHERE GuSNum=@nClubS AND GuPNum=@nClubP AND GuFlag=0 AND GuAlliance=0

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	-- CLUB_BATTLE_DRAW, CLUB_BATTLE_ARMISTICE
	IF (@nGuFlag = 1) OR (@nGuFlag = 2) 
	BEGIN
		UPDATE GuildInfo
        SET GuBattleDraw=GuBattleDraw+1
        WHERE GuNum = @nClubP
	END

	-- CLUB_BATTLE_LOSE, CLUB_BATTLE_SUBMISSION
	IF (@nGuFlag = 5 ) OR (@nGuFlag = 3) 
	BEGIN
		UPDATE GuildInfo
        SET GuBattleLose=GuBattleLose+1
        WHERE GuNum = @nClubP
	END

	-- CLUB_BATTLE_WIN, CLUB_BATTLE_SUBMISSION_WIN
	IF (@nGuFlag = 6 ) OR (@nGuFlag = 4)
	BEGIN
		UPDATE GuildInfo
        SET GuBattleWin=GuBattleWin+1
        WHERE GuNum = @nClubP
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_Extreme]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- ??? ?/? ?? ??? ????.
CREATE   PROCEDURE [dbo].[sp_Extreme]
	@nUserNum	int

AS	
	DECLARE
		@error_var int, 
		@rowcount_var int	

	SET NOCOUNT ON
Select (MSum-MS) As M, (FSum-FS) As F
From
(
	Select isnull(Sum(M),0) As MSum, isnull(Sum(F),0) As FSum, isnull(Sum(MS),0) As MS, isnull(Sum(FS),0) As FS
	From
	(
	Select ChaClass
	,
	Case ChaClass
	When 1 Then 1
	When 2 Then 1
	When 256 Then 1
	When 512 Then 1
	Else 0
	End As M
	,
	Case ChaClass
	When 4 Then 1
	When 8 Then 1
	When 64 Then 1
	When 128 Then 1
	Else 0
	End As F
	,
	Case ChaClass
	When 16 Then 
		Case ChaDeleted
		When 1 Then 0
		Else 1
		End
	Else 0
	End As MS
	,
	Case ChaClass
	When 32 Then 
		Case ChaDeleted
		When 1 Then 0
		Else 1
		End
	Else 0
	End As FS
	From ChaInfo Where UserNum=@nUserNum And (
	( ChaClass=16 OR ChaClass=32 ) 
	OR ( ( ChaClass=1 OR ChaClass=2 OR ChaClass=4 OR ChaClass=8 OR ChaClass=64 OR ChaClass=128 OR ChaClass=256 OR ChaClass=512 ) AND ChaLevel>=190 ) )
	) As t
) As tt
GO
/****** Object:  StoredProcedure [dbo].[sp_GetPetFull]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- Return
-- DB_ERROR -1
-- Full amount
create PROCEDURE [dbo].[sp_GetPetFull]
	@nChaNum	int,
	@nPetNum	int,	
	@nReturn	int OUTPUT
AS
	DECLARE
		@error_var int,
		@rowcount_var int,
		@PetFull int
	
	SET NOCOUNT ON
	
	SET @nReturn = 0

	SELECT @PetFull = PetFull
	FROM PetInfo
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum And PetDeleted=0	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = @PetFull
	END
	
	SET NOCOUNT OFF
	RETURN @nReturn


GO
/****** Object:  StoredProcedure [dbo].[sp_GetVehicleBattery]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- Battery amount
CREATE PROCEDURE [dbo].[sp_GetVehicleBattery]
	@nVehicleNum	int,
	@nVehicleChaNum	int,
	@nReturn	int OUTPUT
AS
	DECLARE
		@error_var int,
		@rowcount_var int,
		@VehicleBattery int
	
	SET NOCOUNT ON
	
	SET @nReturn = 0

	SELECT @VehicleBattery = VehicleBattery
	FROM VehicleInfo
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum=@nVehicleChaNum
	AND VehicleDeleted=0	
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = @VehicleBattery
	END
	
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertAttendLog]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_InsertAttendLog]
	@UserNum	int,
	@nCount	int,
	@nReward int,
	@nReturn	int OUTPUT
AS	

/*
Created by PrinceOfPersia
August 8, 2011
*/

DECLARE @exist int;
		
SET NOCOUNT ON;

SET @nReturn = -1;

BEGIN TRAN

SELECT @EXIST =  COUNT(1) FROM Attendance(NOLOCK) WHERE UserNum = @UserNum;

IF @EXIST= 0
BEGIN
	INSERT INTO Attendance(
	UserNum,
	DaysCount,
	RewardCount,
	AttendDate
	)
	VALUES (
	@UserNum,
	1,
	@nReward,
	GETDATE()
	)		
END
ELSE
BEGIN 
	UPDATE Attendance 
	SET DaysCount = @nCount, 
	RewardCount = @nReward,
	AttendDate = GETDATE()
	WHERE UserNum = @UserNum;
END

IF @@ERROR = 0 
	BEGIN 
		COMMIT TRAN;
		SET @nReturn = 0;
	END

SET NOCOUNT OFF;
RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_InsertEquipmentPass]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_InsertEquipmentPass]
	@nChaNum int,
	@szChaEPass varchar(4),
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nNum int,
		@nCharNum int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nNum = 0
	SET @nCharNum = 0

	SELECT @nCharNum=ChaInfo.ChaNum    
    FROM ChaInfo
    WHERE ChaNum = @nChaNum

    IF @nCharNum = 0
    BEGIN    
		--char not exist  
        SET @nReturn = 2  
        SET NOCOUNT OFF     
        RETURN @nReturn 
    END
    
	SELECT @nNum=ChaEquipmentPass.Num    
    FROM ChaEquipmentPass
    WHERE ChaNum = @nChaNum

    IF @nNum > 0
    BEGIN    
		 --data exist
        SET @nReturn = 1   
        SET NOCOUNT OFF    
        RETURN @nReturn 
    END
    
	--insert new data
	Insert Into ChaEquipmentPass ( ChaNum, ChaEPass )
	Values (@nChaNum, @szChaEPass )
	
	--check inserted
    UPDATE ChaEquipmentPass
    SET ChaEPass=@szChaEPass
    WHERE ChaNum=@nChaNum
    
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
      -- update chainfo 
        UPDATE ChaInfo 
        SET ChaEquipmentLockEnable = 1 
        WHERE ChaNum=@nChaNum 
        
        SET @nReturn = 0
        SET NOCOUNT OFF
        RETURN @nReturn
    END    
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertPet]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[sp_InsertPet]
	@szPetName	  varchar(20),
	@nPetChaNum	  int,
	@nPetType	  int,
	@nPetMID	  int,
	@nPetSID	  int,
	@nPetCardMID       int,
	@nPetCardSID  	  int,
	@nPetStyle	  int,
	@nPetColor	  int,
	@nReturn	  int OUTPUT
As
	DECLARE
		@error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	SET @nReturn = 0

	BEGIN TRAN

	Insert Into PetInfo (PetName, PetChaNum, PetType, PetMID, PetSID, PetCardMID, PetCardSID, PetStyle, PetColor, PetPutOnItems)
	Values (@szPetName, @nPetChaNum, @nPetType, @nPetMID, @nPetSID, @nPetCardMID, @nPetCardSID, @nPetStyle, @nPetColor, '')
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		UPDATE PetInfo SET PetNum = @@IDENTITY WHERE PetUniqueNum = @@IDENTITY
		SET @nReturn = @@IDENTITY
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_InsertVehicle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return (nReturn)
-- DB_ERROR -1
-- DB_OK 0

-- Return (nVehicleNum)

CREATE PROCEDURE [dbo].[sp_InsertVehicle]
	@szVehicleName	  varchar(20),
	@nVehicleChaNum	  int,
	@nVehicleType	  int,	
	@nVehicleCardMID  int,
	@nVehicleCardSID  int,
	@nReturn		  int OUTPUT
As
	DECLARE
		@error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	SET @nReturn = 0

	BEGIN TRAN

	INSERT INTO VehicleInfo (VehicleName, VehicleChaNum, VehicleType, VehicleCardMID, VehicleCardSID, VehiclePutOnItems)
	VALUES (@szVehicleName, @nVehicleChaNum, @nVehicleType, @nVehicleCardMID, @nVehicleCardSID, '')
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		UPDATE VehicleInfo SET VehicleNum=@@IDENTITY WHERE VehicleUniqueNum = @@IDENTITY
		SET @nReturn = @@IDENTITY
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_PKRecordUpdate]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_PKRecordUpdate]
	@nChaNum int,
	@nChaKillNum int,
	@szChaKillName varchar(33),
	@nChaPKRecord int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int,
		@nChaKillNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0
	SET @nChaKillNumTemp = 0
	
	--insert new pkrecord
	Insert Into PKRecord ( ChaNum, ChaKillNum, ChaKillName, ChaPKRecord )
	Values (@nChaNum, @nChaKillNum, @szChaKillName, @nChaPKRecord )
	
	--update pkrecord
    UPDATE ChaInfo
    SET ChaPkRecord=@nChaPKRecord
    WHERE ChaNum=@nChaNum
    
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
/****** Object:  StoredProcedure [dbo].[sp_RenamePet]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_RenamePet]
	@nChaNum	int,
	@nPetNum	int,
	@szPetName	varchar(20),
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nPetNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nPetNumTemp = 0
	
	SELECT @nPetNumTemp=PetNum FROM PetInfo WHERE PetName=@szPetName
	
	IF @nPetNumTemp <> 0 -- Exist PET Name
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		BEGIN TRAN

		UPDATE PetInfo
		SET PetName=@szPetName
		WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
		IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
		END
		ELSE
		BEGIN
			COMMIT TRAN
			SET @nReturn = 0
		END    
	END

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_RequestGuBattle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_RequestGuBattle]
    @nClubP  int,
    @nClubS  int,
	@nStartTime datetime,
	@nEndTime datetime,
	@nAlliance int,
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    INSERT INTO GuildBattle (GuSNum, GuPNum, GuFlag, GuKillNum, GuDeathNum, GuBattleStartDate, GuBattleEndDate, GuAlliance) 
    VALUES (@nClubS, @nClubP, 0, 0, 0, @nStartTime, @nEndTime, @nAlliance)
    
    -- Check Error
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1 -- ERROR
    END
    ELSE
    BEGIN
        SET @nReturn = 0 -- SUCCESS
    END


	UPDATE GuildInfo
    SET GuBattleLastTime=@nStartTime
    WHERE GuNum = @nClubP

	SET NOCOUNT OFF
    RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_ResetAllianceBattle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_ResetAllianceBattle]
    @GuNum  int,
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    BEGIN TRAN

	UPDATE GuildInfo
	SET GuAllianceBattleLose=0, GuAllianceBattleDraw=0, GuAllianceBattleWin=0
	WHERE GuNum=@GuNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_RestorePet]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return (nReturn)
-- DB_ERROR -1
-- DB_OK 0

-- Return (nPetNum)

CREATE PROCEDURE [dbo].[sp_RestorePet]
	@nPetNum	int,
	@nPetChaNum	int,
	@nReturn	int OUTPUT
As
	DECLARE
		@error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	SET @nReturn = 0

	BEGIN TRAN

	Update PetInfo Set PetDeleted=0, PetFull=1000, PetPutOnItems=''
	Where PetNum=@nPetNum And PetChaNum=@nPetChaNum And PetDeleted=1
	
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = @nPetNum
	END

	SET NOCOUNT OFF
	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_SaveGuBattle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_SaveGuBattle]
    @nClubP  int,
    @nClubS  int,
	@nGuKillNum int, 
	@nGuDeathNum int,
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    BEGIN TRAN

	UPDATE GuildBattle
	SET GuKillNum=@nGuKillNum, GuDeathNum=@nGuDeathNum
	WHERE GuSNum=@nClubS AND GuPNum=@nClubP AND GuFlag=0

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_SelectPet]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_SelectPet]
	@nPetNum		int,
	@nReturn		int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	SELECT PetNum, PetName, PetChaNum, PetType, PetMID, PetSID, PetStyle, PetColor, PetFull, PetDeleted, PetCreateDate, PetDeletedDate
	FROM PetInfo
	WHERE PetNum=@nPetNum And PetDeleted=0

	SELECT @error_var = @@ERROR

	IF @error_var <> 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = 0
	END    

	SELECT PetInvenNum, PetNum, PetInvenType, PetInvenMID, PetInvenSID, PetInvenCMID, PetInvenCSID, PetInvenAvailable, PetInvenUpdateDate
	FROM PetInven
	Where PetNum=@nPetNum
	Order By PetInvenType, PetInvenMID, PetInvenSID

	SELECT @error_var = @error_var+@@ERROR, @rowcount_var = @@ROWCOUNT

	IF @error_var <> 0
	BEGIN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		SET @nReturn = 0
	END    


	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_SelectVehicle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_SelectVehicle]
	@nVehicleNum		int,
	@nVehicleChaNum		int
AS
	SET NOCOUNT ON
	
	SELECT VehicleChaNum, VehicleCardMID, VehicleCardSID,
	VehicleType, VehicleBattery, VehicleBooster FROM VehicleInfo WHERE VehicleNum = @nVehicleNum And VehicleChaNum = @nVehicleChaNum

	SET NOCOUNT OFF	

GO
/****** Object:  StoredProcedure [dbo].[sp_update_guild_rank]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_update_guild_rank]
    @nGuNum int,
    @nRank  int,	
	@nReturn int	OUTPUT
AS    
    DECLARE 
        @error_var int, 
		@rowcount_var int

	SET NOCOUNT ON
	
	SET @nReturn = 0	
	SET @error_var = 0
	SET @rowcount_var = 0	
    
    -- Set Guild Rank
    UPDATE GuildInfo 
    SET GuRank=@nRank 
    WHERE GuNum=@nGuNum
    
    -- Check Error
    SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
    IF @error_var <> 0 OR @rowcount_var = 0
    BEGIN
        SET @nReturn = -1 -- ERROR
        SET NOCOUNT OFF
        RETURN @nReturn
    END
    ELSE
    BEGIN
        SET @nReturn = 0 -- SUCCESS
        SET NOCOUNT OFF
        RETURN @nReturn
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdateChaGender]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[sp_UpdateChaGender]
	@nChaNum int,
	@nChaClass int,
	@nChaSex int,
	@nFace int,
	@nChaHair int,
	@nChaHairColor int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn=0
	SET @nChaNumTemp=0
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaClass=@nChaClass, ChaSex=@nChaSex, ChaFace=@nFace, ChaHair=@nChaHair, ChaHairColor=@nChaHairColor
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn
	END

GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetChaNum]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetChaNum]
	@nPetChaNum	int,
	@nPetNum	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetChaNum=@nPetChaNum
	WHERE PetNum=@nPetNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetColor]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetColor]
	@nChaNum	int,
	@nPetNum	int,
	@nPetColor	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetColor=@nPetColor
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetDualSkill]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetDualSkill]
	@nChaNum	int,
	@nPetNum	int,
	@nPetDualSkill	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetDualSkill=@nPetDualSkill
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn


GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetFull]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetFull]
	@nChaNum	int,
	@nPetNum	int,
	@nPetFull	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetFull=@nPetFull
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetInven]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetInven]
	@nChaNum			int,
	@nPetNum		    int,
	@nPetInvenType		int,
	@nPetInvenMID		int,
	@nPetInvenSID		int,
	@nPetInvenCMID		int,
	@nPetInvenCSID		int,
	@nPetInvenAvailable	int,
	@nReturn		int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	-- @nPetInvenType = 1 : Accessory for A type
	-- @nPetInvenType = 2 : Accessory for B type
	-- @nPetInvenType = 3 : Skll

	If @nPetInvenType=1 OR @nPetInvenType=2
	BEGIN
		UPDATE PetInven
		SET PetInvenMID = @nPetInvenMID
		, PetInvenSID = @nPetInvenSID
		, PetInvenCMID = @nPetInvenCMID
		, PetInvenCSID = @nPetInvenCSID
		, PetInvenUpdateDate = getdate()		
		WHERE PetNum = @nPetNum And PetChaNum=@nChaNum
		And PetInvenType = @nPetInvenType
	END
	Else If @nPetInvenType=3
	BEGIN
		UPDATE PetInven
		SET PetInvenCMID = @nPetInvenCMID
		, PetInvenCSID = @nPetInvenCSID
		, PetInvenAvailable = @nPetInvenAvailable
		, PetInvenUpdateDate = getdate()		
		WHERE PetNum = @nPetNum
		And PetChaNum = @nChaNum
		And PetInvenType = @nPetInvenType
		And PetInvenMID = @nPetInvenMID
		And PetInvenSID = @nPetInvenSID
	END

	-- PetInven Update Return Result
	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    

	IF @error_var <> 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	IF (@error_var=0 AND @rowcount_var=0)
	BEGIN
		BEGIN TRAN		

		INSERT INTO PetInven (PetNum, PetChaNum, PetInvenType, PetInvenMID, PetInvenSID, PetInvenCMID, PetInvenCSID, PetInvenAvailable)
		Values (@nPetNum, @nChaNum, @nPetInvenType, @nPetInvenMID, @nPetInvenSID, @nPetInvenCMID, @nPetInvenCSID, @nPetInvenAvailable)

		SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	
		IF @error_var <> 0 OR @rowcount_var = 0
		BEGIN
			ROLLBACK TRAN
			SET @nReturn = -1
		END
		ELSE
		BEGIN
			COMMIT TRAN
			SET @nReturn = 0
		END    
	END
	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetSkin]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetSkin]
	@nChaNum	int,
	@nPetNum	int,
	@nPetSkinMID	int,
	@nPetSkinSID	int,
	@nPetSkinScale	int,
	@nPetSkinTime	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetSkinMID=@nPetSkinMID, PetSkinSID=@nPetSkinSID, PetSkinScale=@nPetSkinScale, PetSkinTime=@nPetSkinTime, PetSkinStartDate = getdate()
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdatePetStyle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdatePetStyle]
	@nChaNum	int,
	@nPetNum	int,
	@nPetStyle	int,
	@nReturn	int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE PetInfo
	SET PetStyle=@nPetStyle
	WHERE PetNum=@nPetNum And PetChaNum=@nChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT    
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_UpdateVehicleBattery]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdateVehicleBattery]
	@nVehicleNum	 int,
	@nVehicleChaNum	 int,
	@nVehicleBattery int,
	@nReturn		int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE VehicleInfo
	SET VehicleBattery=@nVehicleBattery
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum = @nVehicleChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn
GO
/****** Object:  StoredProcedure [dbo].[sp_UpdateVehicleBooster]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- Return
-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[sp_UpdateVehicleBooster]
	@nVehicleNum	 int,
	@nVehicleChaNum	 int,
	@nVehicleBooster int,
	@nReturn		int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0	
	
	BEGIN TRAN

	UPDATE VehicleInfo
	SET VehicleBooster=@nVehicleBooster
	WHERE VehicleNum=@nVehicleNum AND VehicleChaNum = @nVehicleChaNum

	SELECT @error_var = @@ERROR, @rowcount_var = @@ROWCOUNT
	IF @error_var <> 0 OR @rowcount_var = 0
	BEGIN
		ROLLBACK TRAN
		SET @nReturn = -1
	END
	ELSE
	BEGIN
		COMMIT TRAN
		SET @nReturn = 0
	END    

	SET NOCOUNT OFF
	RETURN @nReturn

GO
/****** Object:  StoredProcedure [dbo].[sp_UserAttendLog]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[sp_UserAttendLog]
@UserNum		int
AS

DECLARE @EXIST int ;
		
SET NOCOUNT ON;

SELECT @EXIST =  COUNT(1) FROM Attendance (NOLOCK) WHERE UserNum = @UserNum;

IF 	@EXIST = 0
BEGIN
	SELECT 0, 0, 0 
	RETURN;	
END;

SELECT AttendDate,DaysCount, RewardCount
FROM Attendance	WHERE UserNum = @UserNum;

SET NOCOUNT OFF;


GO
/****** Object:  StoredProcedure [dbo].[UpdateAllCharacterOffline]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateAllCharacterOffline]
AS
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	UPDATE ChaInfo WITH (UPDLOCK) 
	SET ChaOnline=0
	WHERE ChaOnline=1
	
    SET NOCOUNT OFF    
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaExp]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateChaExp]
	@llExp money,
	@nChaNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    UPDATE ChaInfo WITH (UPDLOCK) 
    SET ChaExp=@llExp
    WHERE ChaNum=@nChaNum
    
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
/****** Object:  StoredProcedure [dbo].[UpdateChaFace]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateChaFace]
	@nChaNum int,
	@nChaFace int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0	
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaFace=@nChaFace
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END	
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaFriend]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- DB_ERROR -1
-- DB_OK 0
CREATE PROCEDURE [dbo].[UpdateChaFriend]
	@nChaP int,
	@nChaS int,
	@nFlag int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	
	UPDATE ChaFriend
	SET ChaFlag=@nFlag
	WHERE ChaP=@nChaP AND ChaS=@nChaS
	
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
/****** Object:  StoredProcedure [dbo].[UpdateChaHairColor]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateChaHairColor]
	@nChaNum int,
	@nChaHairColor int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0	
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaHairColor=@nChaHairColor
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END	

GO
/****** Object:  StoredProcedure [dbo].[UpdateChaHairStyle]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateChaHairStyle]
	@nChaNum int,
	@nChaHairStyle int,
	@nReturn int OUTPUT
AS
	DECLARE
		@error_var int, 
		@rowcount_var int,
		@nChaNumTemp int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0
	SET @nChaNumTemp = 0	
	
	IF EXISTS(SELECT ChaNum FROM ChaInfo WHERE ChaNum=@nChaNum)
	BEGIN
		UPDATE ChaInfo SET ChaHair=@nChaHairStyle
		WHERE ChaNum=@nChaNum
		
		SET @nReturn=0
		SET NOCOUNT OFF
		RETURN @nReturn
	END
	ELSE
	BEGIN
		SET @nReturn=-1
		SET NOCOUNT OFF
		RETURN @nReturn	
	END	
GO
/****** Object:  StoredProcedure [dbo].[UpdateChaLastCallPos]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateChaLastCallPos]
	@nChaReturnMap int,
	@fChaReturnPosX float,
	@fChaReturnPosY float,
	@fChaReturnPosZ float,
	@nChaNum int,
	@nReturn int OUTPUT
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	SET @nReturn = 0

    UPDATE ChaInfo SET
    ChaReturnMap=@nChaReturnMap,
    ChaReturnPosX=@fChaReturnPosX,
    ChaReturnPosY=@fChaReturnPosY,
    ChaReturnPosZ=@fChaReturnPosZ
    WHERE ChaNum=@nChaNum    
    
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
/****** Object:  StoredProcedure [dbo].[UpdateChaOnline]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateChaOnline]
	@nChaNum int,
	@nChaOnline int
AS	
	DECLARE
		@error_var int, 
		@rowcount_var int
		
	SET NOCOUNT ON
	
	UPDATE ChaInfo
	SET ChaOnline=@nChaOnline 
	WHERE ChaNum=@nChaNum
	
    SET NOCOUNT OFF    
GO
/****** Object:  StoredProcedure [dbo].[UpdateUserMoney]    Script Date: 1/23/2024 10:57:12 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UpdateUserMoney]    
    @nUserNum int,
    @llMoney money
AS		
	SET NOCOUNT ON
	
	UPDATE UserInven
	SET UserMoney=@llMoney
	WHERE UserNum=@nUserNum

	SET NOCOUNT OFF
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "GuildInfo"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 114
               Right = 220
            End
            DisplayFlags = 280
            TopColumn = 20
         End
         Begin Table = "ChaInfo"
            Begin Extent = 
               Top = 6
               Left = 258
               Bottom = 114
               Right = 417
            End
            DisplayFlags = 280
            TopColumn = 68
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'viewGuildInfo'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'viewGuildInfo'
GO
USE [master]
GO
ALTER DATABASE [RanGame1] SET  READ_WRITE 
GO
