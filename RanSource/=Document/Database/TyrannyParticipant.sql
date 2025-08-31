USE [RanLog]
GO

/****** Object:  Table [dbo].[TyrannyParticipant]    Script Date: 09/09/2021 4:25:23 pm ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[TyrannyParticipant](
	[idx] [bigint] IDENTITY(1,1) NOT NULL,
	[SessionNum] [bigint] NOT NULL,
	[ChaNum] [bigint] NOT NULL,
	[ChaName] [varchar](33) NOT NULL,
	[ChaSchool] [bigint] NOT NULL,
	[ChaClass] [bigint] NOT NULL,
	[RankAll] [bigint] NOT NULL,
	[RankSchool] [bigint] NOT NULL,
	[ScoreKill] [bigint] NOT NULL,
	[ScoreDeath] [bigint] NOT NULL,
	[ScoreDamage] [bigint] NOT NULL,
	[ScoreHeal] [bigint] NOT NULL,
	[ScoreResu] [bigint] NOT NULL,
	[ScoreTotal] [bigint] NOT NULL,
	[RewardPoint] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_TyrannyParticipant] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_SessionNum]  DEFAULT ((0)) FOR [SessionNum]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ChaNum]  DEFAULT ((0)) FOR [ChaNum]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ChaName]  DEFAULT ('') FOR [ChaName]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ChaSchool]  DEFAULT ((0)) FOR [ChaSchool]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ChaClass]  DEFAULT ((0)) FOR [ChaClass]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_RankAll]  DEFAULT ((0)) FOR [RankAll]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_RankSchool]  DEFAULT ((0)) FOR [RankSchool]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ScoreKill]  DEFAULT ((0)) FOR [ScoreKill]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ScoreDeath]  DEFAULT ((0)) FOR [ScoreDeath]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ScoreDamage]  DEFAULT ((0)) FOR [ScoreDamage]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ScoreHeal]  DEFAULT ((0)) FOR [ScoreHeal]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ScoreResu]  DEFAULT ((0)) FOR [ScoreResu]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_ScoreTotal]  DEFAULT ((0)) FOR [ScoreTotal]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_RewardPoint]  DEFAULT ((0)) FOR [RewardPoint]
GO

ALTER TABLE [dbo].[TyrannyParticipant] ADD  CONSTRAINT [DF_TyrannyParticipant_Data]  DEFAULT (getdate()) FOR [Date]
GO


