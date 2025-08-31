USE [RanGame1]
GO

/****** Object:  StoredProcedure [dbo].[PersonalLockCheck]    Script Date: 01/15/2020 07:00:21 ******/
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


