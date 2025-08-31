USE [RanLog]
GO
/****** Object:  StoredProcedure [dbo].[sp_gm_logs_insert]    Script Date: 08/15/2018 04:06:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[sp_gm_logs_insert]
	@nUserID int,
	@nUserType int,
    @nCharID int,
    @szCharName	varchar(33),
    @szCommandInfo	varchar(1024),
	@nReturn	int OUTPUT
AS	
	DECLARE 
        @error_var int,
        @rowcount_var int

    SET NOCOUNT ON

    SET @nReturn = 0
    
	BEGIN TRAN
	
	INSERT INTO gm_logs ( GMUserID, GMUserType, GMCharID, GMCharName, GMCommand )
	VALUES ( @nUserID, @nUserType, @nCharID, @szCharName, @szCommandInfo )

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




