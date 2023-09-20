
#if MSG_METHOD == 1
DCL_MSG(I_glbMsgFile)
#else
#define I_glbMsgFile mkMsgID(8,1)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_languagecodes)
#else
#define I_languagecodes mkMsgID(8,2)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_UserBreak)
#else
#define E_UserBreak mkMsgID(8,3)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_internalFailure)
#else
#define E_internalFailure mkMsgID(8,4)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noMem)
#else
#define E_noMem mkMsgID(8,5)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noFarMem)
#else
#define E_noFarMem mkMsgID(8,6)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_openFile)
#else
#define E_openFile mkMsgID(8,7)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_createFile)
#else
#define E_createFile mkMsgID(8,8)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_accessFile)
#else
#define E_accessFile mkMsgID(8,9)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_readFile)
#else
#define E_readFile mkMsgID(8,10)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_writeFile)
#else
#define E_writeFile mkMsgID(8,11)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_option)
#else
#define E_option mkMsgID(8,12)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_nonArgOption)
#else
#define E_nonArgOption mkMsgID(8,13)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_argOption)
#else
#define E_argOption mkMsgID(8,14)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_argMissing)
#else
#define E_argMissing mkMsgID(8,15)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_msgBuffer)
#else
#define E_msgBuffer mkMsgID(8,16)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_warning)
#else
#define I_warning mkMsgID(8,17)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_error)
#else
#define I_error mkMsgID(8,18)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_fatal)
#else
#define I_fatal mkMsgID(8,19)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_appName)
#else
#define I_appName mkMsgID(8,20)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_noise)
#else
#define I_noise mkMsgID(8,21)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_internalKeywords)
#else
#define I_internalKeywords mkMsgID(8,22)
#endif

#if MSG_METHOD == 1
DCL_MSG(I_locMsgFile)
#else
#define I_locMsgFile mkMsgID(0,23)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_hlpScreen)
#else
#define E_hlpScreen mkMsgID(0,24)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_diffHlpScreen)
#else
#define E_diffHlpScreen mkMsgID(0,25)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_diffCopyHlpScreen)
#else
#define E_diffCopyHlpScreen mkMsgID(0,26)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_ANSIToken)
#else
#define E_ANSIToken mkMsgID(0,27)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_ANSIdoubleNumericArg)
#else
#define E_ANSIdoubleNumericArg mkMsgID(0,28)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_ANSInumericArg)
#else
#define E_ANSInumericArg mkMsgID(0,29)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_encloserOpen)
#else
#define E_encloserOpen mkMsgID(0,30)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_missingInternal)
#else
#define E_missingInternal mkMsgID(0,31)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_msgFileHeadErrLvl)
#else
#define E_msgFileHeadErrLvl mkMsgID(0,32)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_msgFileHeadStruc)
#else
#define E_msgFileHeadStruc mkMsgID(0,33)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_tooManyDefFiles)
#else
#define E_tooManyDefFiles mkMsgID(0,34)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_readInternal)
#else
#define M_readInternal mkMsgID(0,35)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_checkInternal)
#else
#define M_checkInternal mkMsgID(0,36)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_createCompRsp)
#else
#define M_createCompRsp mkMsgID(0,37)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_compRsp)
#else
#define W_compRsp mkMsgID(0,38)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_createLibRsp)
#else
#define M_createLibRsp mkMsgID(0,39)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_libRsp)
#else
#define W_libRsp mkMsgID(0,40)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_createDefFiles)
#else
#define M_createDefFiles mkMsgID(0,41)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_createDecFile)
#else
#define M_createDecFile mkMsgID(0,42)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_decFile)
#else
#define W_decFile mkMsgID(0,43)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_renDecFile)
#else
#define E_renDecFile mkMsgID(0,44)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_removeFile)
#else
#define E_removeFile mkMsgID(0,45)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_removeDir)
#else
#define E_removeDir mkMsgID(0,46)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_permissionRemoveDir)
#else
#define W_permissionRemoveDir mkMsgID(0,47)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_matchFile)
#else
#define W_matchFile mkMsgID(0,48)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_delFile)
#else
#define M_delFile mkMsgID(0,49)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_delDir)
#else
#define M_delDir mkMsgID(0,50)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_longStr)
#else
#define E_longStr mkMsgID(0,51)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdLine)
#else
#define E_cmdLine mkMsgID(0,52)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_exec)
#else
#define E_exec mkMsgID(0,53)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_numberHigh)
#else
#define E_numberHigh mkMsgID(0,54)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_specFmt)
#else
#define E_specFmt mkMsgID(0,55)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noChar)
#else
#define E_noChar mkMsgID(0,56)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_unknownInternal)
#else
#define E_unknownInternal mkMsgID(0,57)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_openEncl)
#else
#define E_openEncl mkMsgID(0,58)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_tooManyMsg)
#else
#define E_tooManyMsg mkMsgID(0,59)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_invalidSpec)
#else
#define E_invalidSpec mkMsgID(0,60)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_createMakedep)
#else
#define M_createMakedep mkMsgID(0,61)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_scanLng)
#else
#define M_scanLng mkMsgID(0,62)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_copyLng)
#else
#define M_copyLng mkMsgID(0,63)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noKeywords)
#else
#define E_noKeywords mkMsgID(0,64)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_inconsistentnr)
#else
#define E_inconsistentnr mkMsgID(0,65)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_makRsp)
#else
#define W_makRsp mkMsgID(0,66)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_createFeature)
#else
#define M_createFeature mkMsgID(0,67)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_rangeOfGroup)
#else
#define E_rangeOfGroup mkMsgID(0,68)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_rangeOfMethod)
#else
#define E_rangeOfMethod mkMsgID(0,69)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_copy)
#else
#define M_copy mkMsgID(0,70)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_renameFile)
#else
#define E_renameFile mkMsgID(0,71)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_tmpFile)
#else
#define E_tmpFile mkMsgID(0,72)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_invalidHlpScreen)
#else
#define E_invalidHlpScreen mkMsgID(0,73)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_keywords)
#else
#define E_keywords mkMsgID(0,74)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_numKeyword)
#else
#define E_numKeyword mkMsgID(0,75)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_defKeyword)
#else
#define E_defKeyword mkMsgID(0,76)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_synKeyword)
#else
#define E_synKeyword mkMsgID(0,77)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noKeyword)
#else
#define E_noKeyword mkMsgID(0,78)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_synSKeyword)
#else
#define E_synSKeyword mkMsgID(0,79)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_numberZero)
#else
#define E_numberZero mkMsgID(0,80)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noCountryCodes)
#else
#define E_noCountryCodes mkMsgID(0,81)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_illformedCountryCodes)
#else
#define E_illformedCountryCodes mkMsgID(0,82)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_msgTooLong)
#else
#define E_msgTooLong mkMsgID(0,83)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_creatMsgFile)
#else
#define M_creatMsgFile mkMsgID(0,84)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_multipleCountryCodes)
#else
#define E_multipleCountryCodes mkMsgID(0,85)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_creatTmpFile)
#else
#define M_creatTmpFile mkMsgID(0,86)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_optOatstart)
#else
#define E_optOatstart mkMsgID(0,87)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_binMsgLib)
#else
#define M_binMsgLib mkMsgID(0,88)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_reqFnam)
#else
#define E_reqFnam mkMsgID(0,89)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_invalidCommand)
#else
#define E_invalidCommand mkMsgID(0,90)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdView)
#else
#define E_cmdView mkMsgID(0,91)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_nocmd)
#else
#define E_nocmd mkMsgID(0,92)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdAlias)
#else
#define E_cmdAlias mkMsgID(0,93)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_invalidNumber)
#else
#define E_invalidNumber mkMsgID(0,94)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdAppend)
#else
#define E_cmdAppend mkMsgID(0,95)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdInsert)
#else
#define E_cmdInsert mkMsgID(0,96)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdRemove)
#else
#define E_cmdRemove mkMsgID(0,97)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_cmdExtract)
#else
#define E_cmdExtract mkMsgID(0,98)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_insertMsgLib)
#else
#define M_insertMsgLib mkMsgID(0,99)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_entryTooHigh)
#else
#define E_entryTooHigh mkMsgID(0,100)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noSuchLng)
#else
#define E_noSuchLng mkMsgID(0,101)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_multPrep)
#else
#define E_multPrep mkMsgID(0,102)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_joinLng)
#else
#define E_joinLng mkMsgID(0,103)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_misLng)
#else
#define E_misLng mkMsgID(0,104)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_multGroup)
#else
#define E_multGroup mkMsgID(0,105)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_noGroup)
#else
#define W_noGroup mkMsgID(0,106)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_longMsgStr)
#else
#define E_longMsgStr mkMsgID(0,107)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_mkTmpFile)
#else
#define E_mkTmpFile mkMsgID(0,108)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_invldTempMode)
#else
#define E_invldTempMode mkMsgID(0,109)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entNoChange)
#else
#define M_entNoChange mkMsgID(0,110)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entOne)
#else
#define M_entOne mkMsgID(0,111)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entMultiple)
#else
#define M_entMultiple mkMsgID(0,112)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entAdded)
#else
#define M_entAdded mkMsgID(0,113)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entRemoved)
#else
#define M_entRemoved mkMsgID(0,114)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entFoundBinLib)
#else
#define M_entFoundBinLib mkMsgID(0,115)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_IOarg)
#else
#define E_IOarg mkMsgID(0,116)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_noEntries)
#else
#define M_noEntries mkMsgID(0,117)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entSepNum)
#else
#define M_entSepNum mkMsgID(0,118)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entNum)
#else
#define M_entNum mkMsgID(0,119)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entLng)
#else
#define M_entLng mkMsgID(0,120)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entCharsets)
#else
#define M_entCharsets mkMsgID(0,121)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entCodepage)
#else
#define M_entCodepage mkMsgID(0,122)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entCSNONE)
#else
#define M_entCSNONE mkMsgID(0,123)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entCS7bitascii)
#else
#define M_entCS7bitascii mkMsgID(0,124)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entCSUnicode16)
#else
#define M_entCSUnicode16 mkMsgID(0,125)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entSepCharset)
#else
#define M_entSepCharset mkMsgID(0,126)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_ent1Charset)
#else
#define M_ent1Charset mkMsgID(0,127)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entEndCharset)
#else
#define M_entEndCharset mkMsgID(0,128)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entAliases)
#else
#define M_entAliases mkMsgID(0,129)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entAlias)
#else
#define M_entAlias mkMsgID(0,130)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entSepAlias)
#else
#define M_entSepAlias mkMsgID(0,131)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_ent1Alias)
#else
#define M_ent1Alias mkMsgID(0,132)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entEndAlias)
#else
#define M_entEndAlias mkMsgID(0,133)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entNoAliases)
#else
#define M_entNoAliases mkMsgID(0,134)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entNoGroups)
#else
#define M_entNoGroups mkMsgID(0,135)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entGroup)
#else
#define M_entGroup mkMsgID(0,136)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entMsgStrings)
#else
#define M_entMsgStrings mkMsgID(0,137)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_entMsg)
#else
#define M_entMsg mkMsgID(0,138)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_creatMsgLib)
#else
#define M_creatMsgLib mkMsgID(0,139)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_emptyMsgLib)
#else
#define W_emptyMsgLib mkMsgID(0,140)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_smallMsgLib)
#else
#define W_smallMsgLib mkMsgID(0,141)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noMsgLib)
#else
#define E_noMsgLib mkMsgID(0,142)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_headBEG)
#else
#define M_headBEG mkMsgID(0,143)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_headEND)
#else
#define M_headEND mkMsgID(0,144)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_brokenMsgLib)
#else
#define E_brokenMsgLib mkMsgID(0,145)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_invldLngCode)
#else
#define E_invldLngCode mkMsgID(0,146)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_creatBinLib)
#else
#define E_creatBinLib mkMsgID(0,147)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_backupBinLib)
#else
#define E_backupBinLib mkMsgID(0,148)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_2mgtHlpScreen)
#else
#define E_2mgtHlpScreen mkMsgID(0,149)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noCharset)
#else
#define E_noCharset mkMsgID(0,150)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_unknownCS)
#else
#define E_unknownCS mkMsgID(0,151)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_readMsgFile)
#else
#define M_readMsgFile mkMsgID(0,152)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_noCharsets)
#else
#define E_noCharsets mkMsgID(0,153)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_lngMultCharsets)
#else
#define W_lngMultCharsets mkMsgID(0,154)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_unknownMsgLibVersion)
#else
#define E_unknownMsgLibVersion mkMsgID(0,155)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_mapMismatch)
#else
#define E_mapMismatch mkMsgID(0,156)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_doubleMsg)
#else
#define E_doubleMsg mkMsgID(0,157)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_dfltMsgIDfn)
#else
#define M_dfltMsgIDfn mkMsgID(0,158)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_scanMsgIDs)
#else
#define M_scanMsgIDs mkMsgID(0,159)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_longLine)
#else
#define E_longLine mkMsgID(0,160)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_syntaxID)
#else
#define E_syntaxID mkMsgID(0,161)
#endif

#if MSG_METHOD == 1
DCL_MSG(E_collGroup)
#else
#define E_collGroup mkMsgID(0,162)
#endif

#if MSG_METHOD == 1
DCL_MSG(W_inclMSGID)
#else
#define W_inclMSGID mkMsgID(0,163)
#endif

#if MSG_METHOD == 1
DCL_MSG(M_compactMsgDB)
#else
#define M_compactMsgDB mkMsgID(0,164)
#endif
