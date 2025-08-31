USE [RanGame1]
GO

/****** Object:  Table [dbo].[GuildBattle]    Script Date: 10/9/2020 2:25:17 PM ******/
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


