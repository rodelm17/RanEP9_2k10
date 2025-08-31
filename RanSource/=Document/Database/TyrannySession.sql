USE [RanLog]
GO

/****** Object:  Table [dbo].[TyrannySession]    Script Date: 09/09/2021 4:25:38 pm ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TyrannySession](
	[SessionNum] [bigint] IDENTITY(1,1) NOT NULL,
	[SchoolWinner] [bigint] NOT NULL,
	[SchoolNumSG] [bigint] NOT NULL,
	[SchoolNumMP] [bigint] NOT NULL,
	[SchoolNumPHX] [bigint] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_TyrannySession] PRIMARY KEY CLUSTERED 
(
	[SessionNum] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[TyrannySession] ADD  CONSTRAINT [DF_TyrannySession_SchoolWinner]  DEFAULT ((0)) FOR [SchoolWinner]
GO

ALTER TABLE [dbo].[TyrannySession] ADD  CONSTRAINT [DF_TyrannySession_SchoolNumSG]  DEFAULT ((0)) FOR [SchoolNumSG]
GO

ALTER TABLE [dbo].[TyrannySession] ADD  CONSTRAINT [DF_Table_1_Data]  DEFAULT (getdate()) FOR [Date]
GO


