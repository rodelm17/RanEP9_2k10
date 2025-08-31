USE [RanGame1]
GO

/****** Object:  StoredProcedure [dbo].[PersonalLockMake]    Script Date: 01/15/2020 07:00:27 ******/
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


