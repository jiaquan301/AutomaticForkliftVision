/*

VTK_LIBHARU_CHANGE this file is new for VTK.

This header file mangles all symbols exported from the libharu library. It is
included in all files while building libharu. Due to namespace pollution, no
libharu headers should be included in .h files in VTK.

To generate this list: wrap everything below in #if 0, build VTK, then
use the following command to obtain the symbol list:

nm libvtkharu.so |grep " [TRD] " | awk '{ print "#define "$3" vtk_haru_"$3 }'

In fact, you must do this on *all* supported platforms and merge the results,
since some symbols are present only on some platforms.

Then alphabetise the list so that future diffs/merges work better.

Note that _fini and _init should be excluded because they are not functions
implemented by the library but are rather created by the linker and
used when the shared library is loaded/unloaded from an executable.

*/

#ifndef vtk_haru_mangle_h
#define vtk_haru_mangle_h

#define ConvertDateToXMDate vtk_haru_ConvertDateToXMDate
#define ExtGState_Check vtk_haru_ExtGState_Check
#define GetElement vtk_haru_GetElement
#define HPDF_3DAnnotExData_New vtk_haru_HPDF_3DAnnotExData_New
#define HPDF_3DAnnotExData_Set3DMeasurement vtk_haru_HPDF_3DAnnotExData_Set3DMeasurement
#define HPDF_3DAnnot_New vtk_haru_HPDF_3DAnnot_New
#define HPDF_3DAnnot_Set3DView vtk_haru_HPDF_3DAnnot_Set3DView
#define HPDF_3DC3DMeasure_New vtk_haru_HPDF_3DC3DMeasure_New
#define HPDF_3DC3DMeasure_SetProjectionAnotation vtk_haru_HPDF_3DC3DMeasure_SetProjectionAnotation
#define HPDF_3DC3DMeasure_SetTextBoxSize vtk_haru_HPDF_3DC3DMeasure_SetTextBoxSize
#define HPDF_3DC3DMeasure_SetText vtk_haru_HPDF_3DC3DMeasure_SetText
#define HPDF_3DMeasure_SetColor vtk_haru_HPDF_3DMeasure_SetColor
#define HPDF_3DMeasure_SetName vtk_haru_HPDF_3DMeasure_SetName
#define HPDF_3DMeasure_SetTextSize vtk_haru_HPDF_3DMeasure_SetTextSize
#define HPDF_3DView_Add3DC3DMeasure vtk_haru_HPDF_3DView_Add3DC3DMeasure
#define HPDF_3DView_AddNode vtk_haru_HPDF_3DView_AddNode
#define HPDF_3DView_New vtk_haru_HPDF_3DView_New
#define HPDF_3DView_SetBackgroundColor vtk_haru_HPDF_3DView_SetBackgroundColor
#define HPDF_3DView_SetCamera vtk_haru_HPDF_3DView_SetCamera
#define HPDF_3DView_SetLighting vtk_haru_HPDF_3DView_SetLighting
#define HPDF_3DView_SetOrthogonalProjection vtk_haru_HPDF_3DView_SetOrthogonalProjection
#define HPDF_3DView_SetPerspectiveProjection vtk_haru_HPDF_3DView_SetPerspectiveProjection
#define HPDF_AddColorspaceFromProfile vtk_haru_HPDF_AddColorspaceFromProfile
#define HPDF_AddIntent vtk_haru_HPDF_AddIntent
#define HPDF_AddPageLabel vtk_haru_HPDF_AddPageLabel
#define HPDF_AddPage vtk_haru_HPDF_AddPage
#define HPDF_Annotation_New vtk_haru_HPDF_Annotation_New
#define HPDF_Annotation_SetBorderStyle vtk_haru_HPDF_Annotation_SetBorderStyle
#define HPDF_Annotation_Validate vtk_haru_HPDF_Annotation_Validate
#define HPDF_Annot_Set3DView vtk_haru_HPDF_Annot_Set3DView
#define HPDF_Annot_SetCMYKColor vtk_haru_HPDF_Annot_SetCMYKColor
#define HPDF_Annot_SetGrayColor vtk_haru_HPDF_Annot_SetGrayColor
#define HPDF_Annot_SetNoColor vtk_haru_HPDF_Annot_SetNoColor
#define HPDF_Annot_SetRGBColor vtk_haru_HPDF_Annot_SetRGBColor
#define HPDF_Array_AddName vtk_haru_HPDF_Array_AddName
#define HPDF_Array_AddNumber vtk_haru_HPDF_Array_AddNumber
#define HPDF_Array_AddReal vtk_haru_HPDF_Array_AddReal
#define HPDF_Array_Add vtk_haru_HPDF_Array_Add
#define HPDF_Array_Clear vtk_haru_HPDF_Array_Clear
#define HPDF_Array_Free vtk_haru_HPDF_Array_Free
#define HPDF_Array_GetItem vtk_haru_HPDF_Array_GetItem
#define HPDF_Array_Insert vtk_haru_HPDF_Array_Insert
#define HPDF_Array_Items vtk_haru_HPDF_Array_Items
#define HPDF_Array_New vtk_haru_HPDF_Array_New
#define HPDF_Array_Write vtk_haru_HPDF_Array_Write
#define HPDF_AToF vtk_haru_HPDF_AToF
#define HPDF_AToI vtk_haru_HPDF_AToI
#define HPDF_AttachFile vtk_haru_HPDF_AttachFile
#define HPDF_Base14FontDef_FindBuiltinData vtk_haru_HPDF_Base14FontDef_FindBuiltinData
#define HPDF_Base14FontDef_New vtk_haru_HPDF_Base14FontDef_New
#define HPDF_BasicEncoder_CopyMap vtk_haru_HPDF_BasicEncoder_CopyMap
#define HPDF_BasicEncoder_FindBuiltinData vtk_haru_HPDF_BasicEncoder_FindBuiltinData
#define HPDF_BasicEncoder_Free vtk_haru_HPDF_BasicEncoder_Free
#define HPDF_BasicEncoder_New vtk_haru_HPDF_BasicEncoder_New
#define HPDF_BasicEncoder_OverrideMap vtk_haru_HPDF_BasicEncoder_OverrideMap
#define HPDF_BasicEncoder_ToUnicode vtk_haru_HPDF_BasicEncoder_ToUnicode
#define HPDF_BasicEncoder_Write vtk_haru_HPDF_BasicEncoder_Write
#define HPDF_Binary_Free vtk_haru_HPDF_Binary_Free
#define HPDF_Binary_GetLen vtk_haru_HPDF_Binary_GetLen
#define HPDF_Binary_GetValue vtk_haru_HPDF_Binary_GetValue
#define HPDF_Binary_New vtk_haru_HPDF_Binary_New
#define HPDF_Binary_SetValue vtk_haru_HPDF_Binary_SetValue
#define HPDF_Binary_Write vtk_haru_HPDF_Binary_Write
#define HPDF_Boolean_New vtk_haru_HPDF_Boolean_New
#define HPDF_Boolean_Write vtk_haru_HPDF_Boolean_Write
#define HPDF_Box_Array_New vtk_haru_HPDF_Box_Array_New
#define HPDF_CallbackReader_New vtk_haru_HPDF_CallbackReader_New
#define HPDF_CallbackWriter_New vtk_haru_HPDF_CallbackWriter_New
#define HPDF_Catalog_AddPageLabel vtk_haru_HPDF_Catalog_AddPageLabel
#define HPDF_Catalog_GetNames vtk_haru_HPDF_Catalog_GetNames
#define HPDF_Catalog_GetPageLayout vtk_haru_HPDF_Catalog_GetPageLayout
#define HPDF_Catalog_GetPageMode vtk_haru_HPDF_Catalog_GetPageMode
#define HPDF_Catalog_GetRoot vtk_haru_HPDF_Catalog_GetRoot
#define HPDF_Catalog_GetViewerPreference vtk_haru_HPDF_Catalog_GetViewerPreference
#define HPDF_Catalog_New vtk_haru_HPDF_Catalog_New
#define HPDF_Catalog_SetNames vtk_haru_HPDF_Catalog_SetNames
#define HPDF_Catalog_SetOpenAction vtk_haru_HPDF_Catalog_SetOpenAction
#define HPDF_Catalog_SetPageLayout vtk_haru_HPDF_Catalog_SetPageLayout
#define HPDF_Catalog_SetPageMode vtk_haru_HPDF_Catalog_SetPageMode
#define HPDF_Catalog_SetViewerPreference vtk_haru_HPDF_Catalog_SetViewerPreference
#define HPDF_Catalog_Validate vtk_haru_HPDF_Catalog_Validate
#define HPDF_CheckError vtk_haru_HPDF_CheckError
#define HPDF_CIDFontDef_AddWidth vtk_haru_HPDF_CIDFontDef_AddWidth
#define HPDF_CIDFontDef_ChangeStyle vtk_haru_HPDF_CIDFontDef_ChangeStyle
#define HPDF_CIDFontDef_FreeFunc vtk_haru_HPDF_CIDFontDef_FreeFunc
#define HPDF_CIDFontDef_FreeWidth vtk_haru_HPDF_CIDFontDef_FreeWidth
#define HPDF_CIDFontDef_GetCIDWidth vtk_haru_HPDF_CIDFontDef_GetCIDWidth
#define HPDF_CIDFontDef_New vtk_haru_HPDF_CIDFontDef_New
#define HPDF_CMapEncoder_AddCMap vtk_haru_HPDF_CMapEncoder_AddCMap
#define HPDF_CMapEncoder_AddCodeSpaceRange vtk_haru_HPDF_CMapEncoder_AddCodeSpaceRange
#define HPDF_CMapEncoder_AddJWWLineHead vtk_haru_HPDF_CMapEncoder_AddJWWLineHead
#define HPDF_CMapEncoder_AddNotDefRange vtk_haru_HPDF_CMapEncoder_AddNotDefRange
#define HPDF_CMapEncoder_ByteType vtk_haru_HPDF_CMapEncoder_ByteType
#define HPDF_CMapEncoder_Free vtk_haru_HPDF_CMapEncoder_Free
#define HPDF_CMapEncoder_InitAttr vtk_haru_HPDF_CMapEncoder_InitAttr
#define HPDF_CMapEncoder_New vtk_haru_HPDF_CMapEncoder_New
#define HPDF_CMapEncoder_SetUnicodeArray vtk_haru_HPDF_CMapEncoder_SetUnicodeArray
#define HPDF_CMapEncoder_ToCID vtk_haru_HPDF_CMapEncoder_ToCID
#define HPDF_CMapEncoder_ToUnicode vtk_haru_HPDF_CMapEncoder_ToUnicode
#define HPDF_CMapEncoder_Write vtk_haru_HPDF_CMapEncoder_Write
#define HPDF_CopyError vtk_haru_HPDF_CopyError
#define HPDF_Create3DView vtk_haru_HPDF_Create3DView
#define HPDF_CreateExtGState vtk_haru_HPDF_CreateExtGState
#define HPDF_CreateJavaScript vtk_haru_HPDF_CreateJavaScript
#define HPDF_CreateOutline vtk_haru_HPDF_CreateOutline
#define HPDF_Destination_New vtk_haru_HPDF_Destination_New
#define HPDF_Destination_SetFitBH vtk_haru_HPDF_Destination_SetFitBH
#define HPDF_Destination_SetFitB vtk_haru_HPDF_Destination_SetFitB
#define HPDF_Destination_SetFitBV vtk_haru_HPDF_Destination_SetFitBV
#define HPDF_Destination_SetFitH vtk_haru_HPDF_Destination_SetFitH
#define HPDF_Destination_SetFitR vtk_haru_HPDF_Destination_SetFitR
#define HPDF_Destination_SetFit vtk_haru_HPDF_Destination_SetFit
#define HPDF_Destination_SetFitV vtk_haru_HPDF_Destination_SetFitV
#define HPDF_Destination_SetXYZ vtk_haru_HPDF_Destination_SetXYZ
#define HPDF_DESTINATION_TYPE_NAMES vtk_haru_HPDF_DESTINATION_TYPE_NAMES
#define HPDF_Destination_Validate vtk_haru_HPDF_Destination_Validate
#define HPDF_Dict_AddBoolean vtk_haru_HPDF_Dict_AddBoolean
#define HPDF_Dict_Add_FilterParams vtk_haru_HPDF_Dict_Add_FilterParams
#define HPDF_Dict_AddName vtk_haru_HPDF_Dict_AddName
#define HPDF_Dict_AddNumber vtk_haru_HPDF_Dict_AddNumber
#define HPDF_Dict_AddPoint3D vtk_haru_HPDF_Dict_AddPoint3D
#define HPDF_Dict_AddReal vtk_haru_HPDF_Dict_AddReal
#define HPDF_Dict_Add vtk_haru_HPDF_Dict_Add
#define HPDF_Dict_Free vtk_haru_HPDF_Dict_Free
#define HPDF_Dict_GetItem vtk_haru_HPDF_Dict_GetItem
#define HPDF_Dict_GetKeyByObj vtk_haru_HPDF_Dict_GetKeyByObj
#define HPDF_Dict_New vtk_haru_HPDF_Dict_New
#define HPDF_Dict_RemoveElement vtk_haru_HPDF_Dict_RemoveElement
#define HPDF_DictStream_New vtk_haru_HPDF_DictStream_New
#define HPDF_Dict_Write vtk_haru_HPDF_Dict_Write
#define HPDF_Doc_AddPagesTo vtk_haru_HPDF_Doc_AddPagesTo
#define HPDF_Doc_FindEncoder vtk_haru_HPDF_Doc_FindEncoder
#define HPDF_Doc_FindFontDef vtk_haru_HPDF_Doc_FindFontDef
#define HPDF_Doc_FindFont vtk_haru_HPDF_Doc_FindFont
#define HPDF_Doc_GetCurrentPages vtk_haru_HPDF_Doc_GetCurrentPages
#define HPDF_Doc_PrepareEncryption vtk_haru_HPDF_Doc_PrepareEncryption
#define HPDF_Doc_RegisterEncoder vtk_haru_HPDF_Doc_RegisterEncoder
#define HPDF_Doc_RegisterFontDef vtk_haru_HPDF_Doc_RegisterFontDef
#define HPDF_Doc_SetCurrentPages vtk_haru_HPDF_Doc_SetCurrentPages
#define HPDF_Doc_SetCurrentPage vtk_haru_HPDF_Doc_SetCurrentPage
#define HPDF_Doc_SetEncryptOff vtk_haru_HPDF_Doc_SetEncryptOff
#define HPDF_Doc_SetEncryptOn vtk_haru_HPDF_Doc_SetEncryptOn
#define HPDF_Doc_Validate vtk_haru_HPDF_Doc_Validate
#define HPDF_EmbeddedFile_New vtk_haru_HPDF_EmbeddedFile_New
#define HPDF_EmbeddedFile_Validate vtk_haru_HPDF_EmbeddedFile_Validate
#define HPDF_Encoder_ByteType vtk_haru_HPDF_Encoder_ByteType
#define HPDF_Encoder_CheckJWWLineHead vtk_haru_HPDF_Encoder_CheckJWWLineHead
#define HPDF_Encoder_Free vtk_haru_HPDF_Encoder_Free
#define HPDF_Encoder_GetByteType vtk_haru_HPDF_Encoder_GetByteType
#define HPDF_Encoder_GetType vtk_haru_HPDF_Encoder_GetType
#define HPDF_Encoder_GetUnicode vtk_haru_HPDF_Encoder_GetUnicode
#define HPDF_Encoder_GetWritingMode vtk_haru_HPDF_Encoder_GetWritingMode
#define HPDF_Encoder_SetParseText vtk_haru_HPDF_Encoder_SetParseText
#define HPDF_Encoder_ToUnicode vtk_haru_HPDF_Encoder_ToUnicode
#define HPDF_Encoder_Validate vtk_haru_HPDF_Encoder_Validate
#define HPDF_Encrypt_CreateEncryptionKey vtk_haru_HPDF_Encrypt_CreateEncryptionKey
#define HPDF_Encrypt_CreateOwnerKey vtk_haru_HPDF_Encrypt_CreateOwnerKey
#define HPDF_Encrypt_CreateUserKey vtk_haru_HPDF_Encrypt_CreateUserKey
#define HPDF_Encrypt_CryptBuf vtk_haru_HPDF_Encrypt_CryptBuf
#define HPDF_EncryptDict_CreateID vtk_haru_HPDF_EncryptDict_CreateID
#define HPDF_EncryptDict_GetAttr vtk_haru_HPDF_EncryptDict_GetAttr
#define HPDF_EncryptDict_New vtk_haru_HPDF_EncryptDict_New
#define HPDF_EncryptDict_OnFree vtk_haru_HPDF_EncryptDict_OnFree
#define HPDF_EncryptDict_Prepare vtk_haru_HPDF_EncryptDict_Prepare
#define HPDF_EncryptDict_SetPassword vtk_haru_HPDF_EncryptDict_SetPassword
#define HPDF_EncryptDict_Validate vtk_haru_HPDF_EncryptDict_Validate
#define HPDF_Encrypt_InitKey vtk_haru_HPDF_Encrypt_InitKey
#define HPDF_Encrypt_Init vtk_haru_HPDF_Encrypt_Init
#define HPDF_Encrypt_Reset vtk_haru_HPDF_Encrypt_Reset
#define HPDF_Error_GetCode vtk_haru_HPDF_Error_GetCode
#define HPDF_Error_GetDetailCode vtk_haru_HPDF_Error_GetDetailCode
#define HPDF_Error_Init vtk_haru_HPDF_Error_Init
#define HPDF_Error_Reset vtk_haru_HPDF_Error_Reset
#define HPDF_ExtGState_New vtk_haru_HPDF_ExtGState_New
#define HPDF_ExtGState_SetAlphaFill vtk_haru_HPDF_ExtGState_SetAlphaFill
#define HPDF_ExtGState_SetAlphaStroke vtk_haru_HPDF_ExtGState_SetAlphaStroke
#define HPDF_ExtGState_SetBlendMode vtk_haru_HPDF_ExtGState_SetBlendMode
#define HPDF_ExtGState_Validate vtk_haru_HPDF_ExtGState_Validate
#define HPDF_FileReader_New vtk_haru_HPDF_FileReader_New
#define HPDF_FileReader_ReadFunc vtk_haru_HPDF_FileReader_ReadFunc
#define HPDF_FileReader_SeekFunc vtk_haru_HPDF_FileReader_SeekFunc
#define HPDF_FileStream_FreeFunc vtk_haru_HPDF_FileStream_FreeFunc
#define HPDF_FileStream_SizeFunc vtk_haru_HPDF_FileStream_SizeFunc
#define HPDF_FileStream_TellFunc vtk_haru_HPDF_FileStream_TellFunc
#define HPDF_FileWriter_New vtk_haru_HPDF_FileWriter_New
#define HPDF_FileWriter_WriteFunc vtk_haru_HPDF_FileWriter_WriteFunc
#define HPDF_FontDef_Cleanup vtk_haru_HPDF_FontDef_Cleanup
#define HPDF_FontDef_Free vtk_haru_HPDF_FontDef_Free
#define HPDF_FontDef_Validate vtk_haru_HPDF_FontDef_Validate
#define HPDF_Font_GetAscent vtk_haru_HPDF_Font_GetAscent
#define HPDF_Font_GetBBox vtk_haru_HPDF_Font_GetBBox
#define HPDF_Font_GetCapHeight vtk_haru_HPDF_Font_GetCapHeight
#define HPDF_Font_GetDescent vtk_haru_HPDF_Font_GetDescent
#define HPDF_Font_GetEncodingName vtk_haru_HPDF_Font_GetEncodingName
#define HPDF_Font_GetFontName vtk_haru_HPDF_Font_GetFontName
#define HPDF_Font_GetUnicodeWidth vtk_haru_HPDF_Font_GetUnicodeWidth
#define HPDF_Font_GetXHeight vtk_haru_HPDF_Font_GetXHeight
#define HPDF_Font_MeasureText vtk_haru_HPDF_Font_MeasureText
#define HPDF_Font_TextWidth vtk_haru_HPDF_Font_TextWidth
#define HPDF_Font_Validate vtk_haru_HPDF_Font_Validate
#define HPDF_FreeDocAll vtk_haru_HPDF_FreeDocAll
#define HPDF_FreeDoc vtk_haru_HPDF_FreeDoc
#define HPDF_FreeMem vtk_haru_HPDF_FreeMem
#define HPDF_FreeTextAnnot_Set2PointCalloutLine vtk_haru_HPDF_FreeTextAnnot_Set2PointCalloutLine
#define HPDF_FreeTextAnnot_Set3PointCalloutLine vtk_haru_HPDF_FreeTextAnnot_Set3PointCalloutLine
#define HPDF_FreeTextAnnot_SetDefaultStyle vtk_haru_HPDF_FreeTextAnnot_SetDefaultStyle
#define HPDF_FreeTextAnnot_SetLineEndingStyle vtk_haru_HPDF_FreeTextAnnot_SetLineEndingStyle
#define HPDF_Free vtk_haru_HPDF_Free
#define HPDF_FToA vtk_haru_HPDF_FToA
#define HPDF_GetContents vtk_haru_HPDF_GetContents
#define HPDF_GetCurrentEncoder vtk_haru_HPDF_GetCurrentEncoder
#define HPDF_GetCurrentPage vtk_haru_HPDF_GetCurrentPage
#define HPDF_GetEncoder vtk_haru_HPDF_GetEncoder
#define HPDF_GetErrorDetail vtk_haru_HPDF_GetErrorDetail
#define HPDF_GetError vtk_haru_HPDF_GetError
#define HPDF_GetFontDef vtk_haru_HPDF_GetFontDef
#define HPDF_GetFont vtk_haru_HPDF_GetFont
#define HPDF_GetInfoAttr vtk_haru_HPDF_GetInfoAttr
#define HPDF_GetMem vtk_haru_HPDF_GetMem
#define HPDF_GetPageByIndex vtk_haru_HPDF_GetPageByIndex
#define HPDF_GetPageLayout vtk_haru_HPDF_GetPageLayout
#define HPDF_GetPageMode vtk_haru_HPDF_GetPageMode
#define HPDF_GetStreamSize vtk_haru_HPDF_GetStreamSize
#define HPDF_GetTTFontDefFromFile vtk_haru_HPDF_GetTTFontDefFromFile
#define HPDF_GetVersion vtk_haru_HPDF_GetVersion
#define HPDF_GetViewerPreference vtk_haru_HPDF_GetViewerPreference
#define HPDF_GryphNameToUnicode vtk_haru_HPDF_GryphNameToUnicode
#define HPDF_GState_Free vtk_haru_HPDF_GState_Free
#define HPDF_GState_New vtk_haru_HPDF_GState_New
#define HPDF_HasDoc vtk_haru_HPDF_HasDoc
#define HPDF_ICC_LoadIccFromMem vtk_haru_HPDF_ICC_LoadIccFromMem
#define HPDF_Image_AddSMask vtk_haru_HPDF_Image_AddSMask
#define HPDF_Image_GetBitsPerComponent vtk_haru_HPDF_Image_GetBitsPerComponent
#define HPDF_Image_GetColorSpace vtk_haru_HPDF_Image_GetColorSpace
#define HPDF_Image_GetHeight vtk_haru_HPDF_Image_GetHeight
#define HPDF_Image_GetSize2 vtk_haru_HPDF_Image_GetSize2
#define HPDF_Image_GetSize vtk_haru_HPDF_Image_GetSize
#define HPDF_Image_GetWidth vtk_haru_HPDF_Image_GetWidth
#define HPDF_Image_Load1BitImageFromMem vtk_haru_HPDF_Image_Load1BitImageFromMem
#define HPDF_Image_LoadJpegImageFromMem vtk_haru_HPDF_Image_LoadJpegImageFromMem
#define HPDF_Image_LoadJpegImage vtk_haru_HPDF_Image_LoadJpegImage
#define HPDF_Image_LoadPngImage vtk_haru_HPDF_Image_LoadPngImage
#define HPDF_Image_LoadRaw1BitImageFromMem vtk_haru_HPDF_Image_LoadRaw1BitImageFromMem
#define HPDF_Image_LoadRawImageFromMem vtk_haru_HPDF_Image_LoadRawImageFromMem
#define HPDF_Image_LoadRawImage vtk_haru_HPDF_Image_LoadRawImage
#define HPDF_Image_SetColorMask vtk_haru_HPDF_Image_SetColorMask
#define HPDF_Image_SetColorSpace vtk_haru_HPDF_Image_SetColorSpace
#define HPDF_Image_SetMaskImage vtk_haru_HPDF_Image_SetMaskImage
#define HPDF_Image_SetMask vtk_haru_HPDF_Image_SetMask
#define HPDF_Image_SetRenderingIntent vtk_haru_HPDF_Image_SetRenderingIntent
#define HPDF_Image_Validate vtk_haru_HPDF_Image_Validate
#define HPDF_Info_GetInfoAttr vtk_haru_HPDF_Info_GetInfoAttr
#define HPDF_Info_SetInfoAttr vtk_haru_HPDF_Info_SetInfoAttr
#define HPDF_Info_SetInfoDateAttr vtk_haru_HPDF_Info_SetInfoDateAttr
#define HPDF_InsertPage vtk_haru_HPDF_InsertPage
#define HPDF_IToA2 vtk_haru_HPDF_IToA2
#define HPDF_IToA vtk_haru_HPDF_IToA
#define HPDF_LineAnnot_SetCaption vtk_haru_HPDF_LineAnnot_SetCaption
#define HPDF_LineAnnot_SetLeader vtk_haru_HPDF_LineAnnot_SetLeader
#define HPDF_LineAnnot_SetPosition vtk_haru_HPDF_LineAnnot_SetPosition
#define HPDF_LinkAnnot_New vtk_haru_HPDF_LinkAnnot_New
#define HPDF_LinkAnnot_SetBorderStyle vtk_haru_HPDF_LinkAnnot_SetBorderStyle
#define HPDF_LinkAnnot_SetHighlightMode vtk_haru_HPDF_LinkAnnot_SetHighlightMode
#define HPDF_List_Add vtk_haru_HPDF_List_Add
#define HPDF_List_Clear vtk_haru_HPDF_List_Clear
#define HPDF_List_Find vtk_haru_HPDF_List_Find
#define HPDF_List_Free vtk_haru_HPDF_List_Free
#define HPDF_List_Insert vtk_haru_HPDF_List_Insert
#define HPDF_List_ItemAt vtk_haru_HPDF_List_ItemAt
#define HPDF_List_New vtk_haru_HPDF_List_New
#define HPDF_List_RemoveByIndex vtk_haru_HPDF_List_RemoveByIndex
#define HPDF_List_Remove vtk_haru_HPDF_List_Remove
#define HPDF_LoadIccProfileFromFile vtk_haru_HPDF_LoadIccProfileFromFile
#define HPDF_LoadJpegImageFromFile vtk_haru_HPDF_LoadJpegImageFromFile
#define HPDF_LoadJpegImageFromMem vtk_haru_HPDF_LoadJpegImageFromMem
#define HPDF_LoadPngImageFromFile2 vtk_haru_HPDF_LoadPngImageFromFile2
#define HPDF_LoadPngImageFromFile vtk_haru_HPDF_LoadPngImageFromFile
#define HPDF_LoadPngImageFromMem vtk_haru_HPDF_LoadPngImageFromMem
#define HPDF_LoadRawImageFromFile vtk_haru_HPDF_LoadRawImageFromFile
#define HPDF_LoadRawImageFromMem vtk_haru_HPDF_LoadRawImageFromMem
#define HPDF_LoadTTFontFromFile2 vtk_haru_HPDF_LoadTTFontFromFile2
#define HPDF_LoadTTFontFromFile vtk_haru_HPDF_LoadTTFontFromFile
#define HPDF_LoadType1FontFromFile vtk_haru_HPDF_LoadType1FontFromFile
#define HPDF_LoadU3DFromFile vtk_haru_HPDF_LoadU3DFromFile
#define HPDF_LoadU3DFromMem vtk_haru_HPDF_LoadU3DFromMem
#define HPDF_MarkupAnnot_New vtk_haru_HPDF_MarkupAnnot_New
#define HPDF_MarkupAnnot_SetCloudEffect vtk_haru_HPDF_MarkupAnnot_SetCloudEffect
#define HPDF_MarkupAnnot_SetCreationDate vtk_haru_HPDF_MarkupAnnot_SetCreationDate
#define HPDF_MarkupAnnot_SetIntent vtk_haru_HPDF_MarkupAnnot_SetIntent
#define HPDF_MarkupAnnot_SetInteriorCMYKColor vtk_haru_HPDF_MarkupAnnot_SetInteriorCMYKColor
#define HPDF_MarkupAnnot_SetInteriorGrayColor vtk_haru_HPDF_MarkupAnnot_SetInteriorGrayColor
#define HPDF_MarkupAnnot_SetInteriorRGBColor vtk_haru_HPDF_MarkupAnnot_SetInteriorRGBColor
#define HPDF_MarkupAnnot_SetInteriorTransparent vtk_haru_HPDF_MarkupAnnot_SetInteriorTransparent
#define HPDF_MarkupAnnot_SetPopup vtk_haru_HPDF_MarkupAnnot_SetPopup
#define HPDF_MarkupAnnot_SetRectDiff vtk_haru_HPDF_MarkupAnnot_SetRectDiff
#define HPDF_MarkupAnnot_SetSubject vtk_haru_HPDF_MarkupAnnot_SetSubject
#define HPDF_MarkupAnnot_SetTitle vtk_haru_HPDF_MarkupAnnot_SetTitle
#define HPDF_MarkupAnnot_SetTransparency vtk_haru_HPDF_MarkupAnnot_SetTransparency
#define HPDF_MD5Final vtk_haru_HPDF_MD5Final
#define HPDF_MD5Init vtk_haru_HPDF_MD5Init
#define HPDF_MD5Update vtk_haru_HPDF_MD5Update
#define HPDF_MemCmp vtk_haru_HPDF_MemCmp
#define HPDF_MemCpy vtk_haru_HPDF_MemCpy
#define HPDF_MemSet vtk_haru_HPDF_MemSet
#define HPDF_MemStream_FreeData vtk_haru_HPDF_MemStream_FreeData
#define HPDF_MemStream_FreeFunc vtk_haru_HPDF_MemStream_FreeFunc
#define HPDF_MemStream_GetBufCount vtk_haru_HPDF_MemStream_GetBufCount
#define HPDF_MemStream_GetBufPtr vtk_haru_HPDF_MemStream_GetBufPtr
#define HPDF_MemStream_GetBufSize vtk_haru_HPDF_MemStream_GetBufSize
#define HPDF_MemStream_InWrite vtk_haru_HPDF_MemStream_InWrite
#define HPDF_MemStream_New vtk_haru_HPDF_MemStream_New
#define HPDF_MemStream_ReadFunc vtk_haru_HPDF_MemStream_ReadFunc
#define HPDF_MemStream_Rewrite vtk_haru_HPDF_MemStream_Rewrite
#define HPDF_MemStream_SeekFunc vtk_haru_HPDF_MemStream_SeekFunc
#define HPDF_MemStream_SizeFunc vtk_haru_HPDF_MemStream_SizeFunc
#define HPDF_MemStream_TellFunc vtk_haru_HPDF_MemStream_TellFunc
#define HPDF_MemStream_WriteFunc vtk_haru_HPDF_MemStream_WriteFunc
#define HPDF_MMgr_Free vtk_haru_HPDF_MMgr_Free
#define HPDF_MMgr_New vtk_haru_HPDF_MMgr_New
#define HPDF_NameDict_GetNameTree vtk_haru_HPDF_NameDict_GetNameTree
#define HPDF_NameDict_New vtk_haru_HPDF_NameDict_New
#define HPDF_NameDict_SetNameTree vtk_haru_HPDF_NameDict_SetNameTree
#define HPDF_NameDict_Validate vtk_haru_HPDF_NameDict_Validate
#define HPDF_Name_GetValue vtk_haru_HPDF_Name_GetValue
#define HPDF_Name_New vtk_haru_HPDF_Name_New
#define HPDF_Name_SetValue vtk_haru_HPDF_Name_SetValue
#define HPDF_NameTree_Add vtk_haru_HPDF_NameTree_Add
#define HPDF_NameTree_New vtk_haru_HPDF_NameTree_New
#define HPDF_NameTree_Validate vtk_haru_HPDF_NameTree_Validate
#define HPDF_Name_Write vtk_haru_HPDF_Name_Write
#define HPDF_NewDoc vtk_haru_HPDF_NewDoc
#define HPDF_NewEx vtk_haru_HPDF_NewEx
#define HPDF_New vtk_haru_HPDF_New
#define HPDF_Null_New vtk_haru_HPDF_Null_New
#define HPDF_Number_New vtk_haru_HPDF_Number_New
#define HPDF_Number_SetValue vtk_haru_HPDF_Number_SetValue
#define HPDF_Number_Write vtk_haru_HPDF_Number_Write
#define HPDF_Obj_ForceFree vtk_haru_HPDF_Obj_ForceFree
#define HPDF_Obj_Free vtk_haru_HPDF_Obj_Free
#define HPDF_Obj_WriteValue vtk_haru_HPDF_Obj_WriteValue
#define HPDF_Obj_Write vtk_haru_HPDF_Obj_Write
#define HPDF_Outline_GetFirst vtk_haru_HPDF_Outline_GetFirst
#define HPDF_Outline_GetLast vtk_haru_HPDF_Outline_GetLast
#define HPDF_Outline_GetNext vtk_haru_HPDF_Outline_GetNext
#define HPDF_Outline_GetOpened vtk_haru_HPDF_Outline_GetOpened
#define HPDF_Outline_GetParent vtk_haru_HPDF_Outline_GetParent
#define HPDF_Outline_GetPrev vtk_haru_HPDF_Outline_GetPrev
#define HPDF_Outline_New vtk_haru_HPDF_Outline_New
#define HPDF_OutlineRoot_New vtk_haru_HPDF_OutlineRoot_New
#define HPDF_Outline_SetDestination vtk_haru_HPDF_Outline_SetDestination
#define HPDF_Outline_SetOpened vtk_haru_HPDF_Outline_SetOpened
#define HPDF_Outline_Validate vtk_haru_HPDF_Outline_Validate
#define HPDF_OutputIntent_New vtk_haru_HPDF_OutputIntent_New
#define HPDF_PadOrTrancatePasswd vtk_haru_HPDF_PadOrTrancatePasswd
#define HPDF_Page_Arc vtk_haru_HPDF_Page_Arc
#define HPDF_Page_BeginText vtk_haru_HPDF_Page_BeginText
#define HPDF_Page_CheckState vtk_haru_HPDF_Page_CheckState
#define HPDF_Page_Circle vtk_haru_HPDF_Page_Circle
#define HPDF_Page_Clip vtk_haru_HPDF_Page_Clip
#define HPDF_Page_ClosePathEofillStroke vtk_haru_HPDF_Page_ClosePathEofillStroke
#define HPDF_Page_ClosePathFillStroke vtk_haru_HPDF_Page_ClosePathFillStroke
#define HPDF_Page_ClosePathStroke vtk_haru_HPDF_Page_ClosePathStroke
#define HPDF_Page_ClosePath vtk_haru_HPDF_Page_ClosePath
#define HPDF_Page_Concat vtk_haru_HPDF_Page_Concat
#define HPDF_Page_Create3DAnnotExData vtk_haru_HPDF_Page_Create3DAnnotExData
#define HPDF_Page_Create3DAnnot vtk_haru_HPDF_Page_Create3DAnnot
#define HPDF_Page_Create3DC3DMeasure vtk_haru_HPDF_Page_Create3DC3DMeasure
#define HPDF_Page_Create3DView vtk_haru_HPDF_Page_Create3DView
#define HPDF_Page_CreateCircleAnnot vtk_haru_HPDF_Page_CreateCircleAnnot
#define HPDF_Page_CreateDestination vtk_haru_HPDF_Page_CreateDestination
#define HPDF_Page_CreateFreeTextAnnot vtk_haru_HPDF_Page_CreateFreeTextAnnot
#define HPDF_Page_CreateHighlightAnnot vtk_haru_HPDF_Page_CreateHighlightAnnot
#define HPDF_Page_CreateLineAnnot vtk_haru_HPDF_Page_CreateLineAnnot
#define HPDF_Page_CreateLinkAnnot vtk_haru_HPDF_Page_CreateLinkAnnot
#define HPDF_Page_CreatePD33DMeasure vtk_haru_HPDF_Page_CreatePD33DMeasure
#define HPDF_Page_CreatePopupAnnot vtk_haru_HPDF_Page_CreatePopupAnnot
#define HPDF_Page_CreateProjectionAnnot vtk_haru_HPDF_Page_CreateProjectionAnnot
#define HPDF_Page_CreateSquareAnnot vtk_haru_HPDF_Page_CreateSquareAnnot
#define HPDF_Page_CreateSquigglyAnnot vtk_haru_HPDF_Page_CreateSquigglyAnnot
#define HPDF_Page_CreateStampAnnot vtk_haru_HPDF_Page_CreateStampAnnot
#define HPDF_Page_CreateStrikeOutAnnot vtk_haru_HPDF_Page_CreateStrikeOutAnnot
#define HPDF_Page_CreateTextAnnot vtk_haru_HPDF_Page_CreateTextAnnot
#define HPDF_Page_CreateTextMarkupAnnot vtk_haru_HPDF_Page_CreateTextMarkupAnnot
#define HPDF_Page_CreateUnderlineAnnot vtk_haru_HPDF_Page_CreateUnderlineAnnot
#define HPDF_Page_CreateURILinkAnnot vtk_haru_HPDF_Page_CreateURILinkAnnot
#define HPDF_Page_CurveTo2 vtk_haru_HPDF_Page_CurveTo2
#define HPDF_Page_CurveTo3 vtk_haru_HPDF_Page_CurveTo3
#define HPDF_Page_CurveTo vtk_haru_HPDF_Page_CurveTo
#define HPDF_Page_DrawImage vtk_haru_HPDF_Page_DrawImage
#define HPDF_Page_Ellipse vtk_haru_HPDF_Page_Ellipse
#define HPDF_Page_EndPath vtk_haru_HPDF_Page_EndPath
#define HPDF_Page_EndText vtk_haru_HPDF_Page_EndText
#define HPDF_Page_Eoclip vtk_haru_HPDF_Page_Eoclip
#define HPDF_Page_EofillStroke vtk_haru_HPDF_Page_EofillStroke
#define HPDF_Page_Eofill vtk_haru_HPDF_Page_Eofill
#define HPDF_Page_ExecuteXObject vtk_haru_HPDF_Page_ExecuteXObject
#define HPDF_Page_FillStroke vtk_haru_HPDF_Page_FillStroke
#define HPDF_Page_Fill vtk_haru_HPDF_Page_Fill
#define HPDF_Page_GetCharSpace vtk_haru_HPDF_Page_GetCharSpace
#define HPDF_Page_GetCMYKFill vtk_haru_HPDF_Page_GetCMYKFill
#define HPDF_Page_GetCMYKStroke vtk_haru_HPDF_Page_GetCMYKStroke
#define HPDF_Page_GetCurrentFontSize vtk_haru_HPDF_Page_GetCurrentFontSize
#define HPDF_Page_GetCurrentFont vtk_haru_HPDF_Page_GetCurrentFont
#define HPDF_Page_GetCurrentPos2 vtk_haru_HPDF_Page_GetCurrentPos2
#define HPDF_Page_GetCurrentPos vtk_haru_HPDF_Page_GetCurrentPos
#define HPDF_Page_GetCurrentTextPos2 vtk_haru_HPDF_Page_GetCurrentTextPos2
#define HPDF_Page_GetCurrentTextPos vtk_haru_HPDF_Page_GetCurrentTextPos
#define HPDF_Page_GetDash vtk_haru_HPDF_Page_GetDash
#define HPDF_Page_GetExtGStateName vtk_haru_HPDF_Page_GetExtGStateName
#define HPDF_Page_GetFillingColorSpace vtk_haru_HPDF_Page_GetFillingColorSpace
#define HPDF_Page_GetFlat vtk_haru_HPDF_Page_GetFlat
#define HPDF_Page_GetGMode vtk_haru_HPDF_Page_GetGMode
#define HPDF_Page_GetGrayFill vtk_haru_HPDF_Page_GetGrayFill
#define HPDF_Page_GetGrayStroke vtk_haru_HPDF_Page_GetGrayStroke
#define HPDF_Page_GetGStateDepth vtk_haru_HPDF_Page_GetGStateDepth
#define HPDF_Page_GetHeight vtk_haru_HPDF_Page_GetHeight
#define HPDF_Page_GetHorizontalScalling vtk_haru_HPDF_Page_GetHorizontalScalling
#define HPDF_Page_GetInheritableItem vtk_haru_HPDF_Page_GetInheritableItem
#define HPDF_Page_GetLineCap vtk_haru_HPDF_Page_GetLineCap
#define HPDF_Page_GetLineJoin vtk_haru_HPDF_Page_GetLineJoin
#define HPDF_Page_GetLineWidth vtk_haru_HPDF_Page_GetLineWidth
#define HPDF_Page_GetLocalFontName vtk_haru_HPDF_Page_GetLocalFontName
#define HPDF_Page_GetMediaBox vtk_haru_HPDF_Page_GetMediaBox
#define HPDF_Page_GetMiterLimit vtk_haru_HPDF_Page_GetMiterLimit
#define HPDF_Page_GetRGBFill vtk_haru_HPDF_Page_GetRGBFill
#define HPDF_Page_GetRGBStroke vtk_haru_HPDF_Page_GetRGBStroke
#define HPDF_Page_GetShadingName vtk_haru_HPDF_Page_GetShadingName
#define HPDF_Page_GetStrokingColorSpace vtk_haru_HPDF_Page_GetStrokingColorSpace
#define HPDF_Page_GetTextLeading vtk_haru_HPDF_Page_GetTextLeading
#define HPDF_Page_GetTextMatrix vtk_haru_HPDF_Page_GetTextMatrix
#define HPDF_Page_GetTextRaise vtk_haru_HPDF_Page_GetTextRaise
#define HPDF_Page_GetTextRenderingMode vtk_haru_HPDF_Page_GetTextRenderingMode
#define HPDF_Page_GetTextRise vtk_haru_HPDF_Page_GetTextRise
#define HPDF_Page_GetTransMatrix vtk_haru_HPDF_Page_GetTransMatrix
#define HPDF_Page_GetWidth vtk_haru_HPDF_Page_GetWidth
#define HPDF_Page_GetWordSpace vtk_haru_HPDF_Page_GetWordSpace
#define HPDF_Page_GetXObjectName vtk_haru_HPDF_Page_GetXObjectName
#define HPDF_Page_GRestore vtk_haru_HPDF_Page_GRestore
#define HPDF_Page_GSave vtk_haru_HPDF_Page_GSave
#define HPDF_Page_InsertBefore vtk_haru_HPDF_Page_InsertBefore
#define HPDF_Page_Insert_Shared_Content_Stream vtk_haru_HPDF_Page_Insert_Shared_Content_Stream
#define HPDF_PageLabel_New vtk_haru_HPDF_PageLabel_New
#define HPDF_Page_LineTo vtk_haru_HPDF_Page_LineTo
#define HPDF_Page_MeasureText vtk_haru_HPDF_Page_MeasureText
#define HPDF_Page_MoveTextPos2 vtk_haru_HPDF_Page_MoveTextPos2
#define HPDF_Page_MoveTextPos vtk_haru_HPDF_Page_MoveTextPos
#define HPDF_Page_MoveToNextLine vtk_haru_HPDF_Page_MoveToNextLine
#define HPDF_Page_MoveTo vtk_haru_HPDF_Page_MoveTo
#define HPDF_Page_New_Content_Stream vtk_haru_HPDF_Page_New_Content_Stream
#define HPDF_Page_New vtk_haru_HPDF_Page_New
#define HPDF_Page_Rectangle vtk_haru_HPDF_Page_Rectangle
#define HPDF_Pages_AddKids vtk_haru_HPDF_Pages_AddKids
#define HPDF_Page_SetBoxValue vtk_haru_HPDF_Page_SetBoxValue
#define HPDF_Page_SetCharSpace vtk_haru_HPDF_Page_SetCharSpace
#define HPDF_Page_SetCMYKFill vtk_haru_HPDF_Page_SetCMYKFill
#define HPDF_Page_SetCMYKStroke vtk_haru_HPDF_Page_SetCMYKStroke
#define HPDF_Page_SetDash vtk_haru_HPDF_Page_SetDash
#define HPDF_Page_SetExtGState vtk_haru_HPDF_Page_SetExtGState
#define HPDF_Page_SetFilter vtk_haru_HPDF_Page_SetFilter
#define HPDF_Page_SetFlat vtk_haru_HPDF_Page_SetFlat
#define HPDF_Page_SetFontAndSize vtk_haru_HPDF_Page_SetFontAndSize
#define HPDF_Page_SetGrayFill vtk_haru_HPDF_Page_SetGrayFill
#define HPDF_Page_SetGrayStroke vtk_haru_HPDF_Page_SetGrayStroke
#define HPDF_Page_SetHeight vtk_haru_HPDF_Page_SetHeight
#define HPDF_Page_SetHorizontalScalling vtk_haru_HPDF_Page_SetHorizontalScalling
#define HPDF_Page_SetLineCap vtk_haru_HPDF_Page_SetLineCap
#define HPDF_Page_SetLineJoin vtk_haru_HPDF_Page_SetLineJoin
#define HPDF_Page_SetLineWidth vtk_haru_HPDF_Page_SetLineWidth
#define HPDF_Page_SetMiterLimit vtk_haru_HPDF_Page_SetMiterLimit
#define HPDF_Page_SetRGBFill vtk_haru_HPDF_Page_SetRGBFill
#define HPDF_Page_SetRGBStroke vtk_haru_HPDF_Page_SetRGBStroke
#define HPDF_Page_SetRotate vtk_haru_HPDF_Page_SetRotate
#define HPDF_Page_SetShading vtk_haru_HPDF_Page_SetShading
#define HPDF_Page_SetSize vtk_haru_HPDF_Page_SetSize
#define HPDF_Page_SetSlideShow vtk_haru_HPDF_Page_SetSlideShow
#define HPDF_Page_SetTextLeading vtk_haru_HPDF_Page_SetTextLeading
#define HPDF_Page_SetTextMatrix vtk_haru_HPDF_Page_SetTextMatrix
#define HPDF_Page_SetTextRaise vtk_haru_HPDF_Page_SetTextRaise
#define HPDF_Page_SetTextRenderingMode vtk_haru_HPDF_Page_SetTextRenderingMode
#define HPDF_Page_SetTextRise vtk_haru_HPDF_Page_SetTextRise
#define HPDF_Page_SetWidth vtk_haru_HPDF_Page_SetWidth
#define HPDF_Page_SetWordSpace vtk_haru_HPDF_Page_SetWordSpace
#define HPDF_Page_SetZoom vtk_haru_HPDF_Page_SetZoom
#define HPDF_Page_ShowTextNextLineEx vtk_haru_HPDF_Page_ShowTextNextLineEx
#define HPDF_Page_ShowTextNextLine vtk_haru_HPDF_Page_ShowTextNextLine
#define HPDF_Page_ShowText vtk_haru_HPDF_Page_ShowText
#define HPDF_Pages_New vtk_haru_HPDF_Pages_New
#define HPDF_Page_Stroke vtk_haru_HPDF_Page_Stroke
#define HPDF_Pages_Validate vtk_haru_HPDF_Pages_Validate
#define HPDF_Page_TextOut vtk_haru_HPDF_Page_TextOut
#define HPDF_Page_TextRect vtk_haru_HPDF_Page_TextRect
#define HPDF_Page_TextWidth vtk_haru_HPDF_Page_TextWidth
#define HPDF_Page_Validate vtk_haru_HPDF_Page_Validate
#define HPDF_PD33DMeasure_New vtk_haru_HPDF_PD33DMeasure_New
#define HPDF_PDFA_AppendOutputIntents vtk_haru_HPDF_PDFA_AppendOutputIntents
#define HPDF_PDFA_GenerateID vtk_haru_HPDF_PDFA_GenerateID
#define HPDF_PDFA_SetPDFAConformance vtk_haru_HPDF_PDFA_SetPDFAConformance
#define HPDF_PopupAnnot_New vtk_haru_HPDF_PopupAnnot_New
#define HPDF_PopupAnnot_SetOpened vtk_haru_HPDF_PopupAnnot_SetOpened
#define HPDF_ProjectionAnnot_New vtk_haru_HPDF_ProjectionAnnot_New
#define HPDF_ProjectionAnnot_SetExData vtk_haru_HPDF_ProjectionAnnot_SetExData
#define HPDF_Proxy_New vtk_haru_HPDF_Proxy_New
#define HPDF_RaiseError vtk_haru_HPDF_RaiseError
#define HPDF_ReadFromStream vtk_haru_HPDF_ReadFromStream
#define HPDF_Real_New vtk_haru_HPDF_Real_New
#define HPDF_Real_SetValue vtk_haru_HPDF_Real_SetValue
#define HPDF_Real_Write vtk_haru_HPDF_Real_Write
#define HPDF_ResetError vtk_haru_HPDF_ResetError
#define HPDF_ResetStream vtk_haru_HPDF_ResetStream
#define HPDF_SaveToFile vtk_haru_HPDF_SaveToFile
#define HPDF_SaveToStream vtk_haru_HPDF_SaveToStream
#define HPDF_SetCompressionMode vtk_haru_HPDF_SetCompressionMode
#define HPDF_SetCurrentEncoder vtk_haru_HPDF_SetCurrentEncoder
#define HPDF_SetEncryptionMode vtk_haru_HPDF_SetEncryptionMode
#define HPDF_SetErrorHandler vtk_haru_HPDF_SetErrorHandler
#define HPDF_SetError vtk_haru_HPDF_SetError
#define HPDF_SetInfoAttr vtk_haru_HPDF_SetInfoAttr
#define HPDF_SetInfoDateAttr vtk_haru_HPDF_SetInfoDateAttr
#define HPDF_SetOpenAction vtk_haru_HPDF_SetOpenAction
#define HPDF_SetPageLayout vtk_haru_HPDF_SetPageLayout
#define HPDF_SetPageMode vtk_haru_HPDF_SetPageMode
#define HPDF_SetPagesConfiguration vtk_haru_HPDF_SetPagesConfiguration
#define HPDF_SetPassword vtk_haru_HPDF_SetPassword
#define HPDF_SetPermission vtk_haru_HPDF_SetPermission
#define HPDF_SetViewerPreference vtk_haru_HPDF_SetViewerPreference
#define HPDF_Shading_AddVertexRGB vtk_haru_HPDF_Shading_AddVertexRGB
#define HPDF_Shading_New vtk_haru_HPDF_Shading_New
#define HPDF_StampAnnot_New vtk_haru_HPDF_StampAnnot_New
#define HPDF_StrCmp vtk_haru_HPDF_StrCmp
#define HPDF_StrCpy vtk_haru_HPDF_StrCpy
#define HPDF_Stream_CcittToStream vtk_haru_HPDF_Stream_CcittToStream
#define HPDF_Stream_Free vtk_haru_HPDF_Stream_Free
#define HPDF_Stream_ReadLn vtk_haru_HPDF_Stream_ReadLn
#define HPDF_Stream_Read vtk_haru_HPDF_Stream_Read
#define HPDF_Stream_Seek vtk_haru_HPDF_Stream_Seek
#define HPDF_Stream_Size vtk_haru_HPDF_Stream_Size
#define HPDF_Stream_Tell vtk_haru_HPDF_Stream_Tell
#define HPDF_Stream_Validate vtk_haru_HPDF_Stream_Validate
#define HPDF_Stream_WriteBinary vtk_haru_HPDF_Stream_WriteBinary
#define HPDF_Stream_WriteChar vtk_haru_HPDF_Stream_WriteChar
#define HPDF_Stream_WriteEscapeName vtk_haru_HPDF_Stream_WriteEscapeName
#define HPDF_Stream_WriteEscapeText2 vtk_haru_HPDF_Stream_WriteEscapeText2
#define HPDF_Stream_WriteEscapeText vtk_haru_HPDF_Stream_WriteEscapeText
#define HPDF_Stream_WriteInt vtk_haru_HPDF_Stream_WriteInt
#define HPDF_Stream_WriteReal vtk_haru_HPDF_Stream_WriteReal
#define HPDF_Stream_WriteStr vtk_haru_HPDF_Stream_WriteStr
#define HPDF_Stream_WriteToStream vtk_haru_HPDF_Stream_WriteToStream
#define HPDF_Stream_WriteToStreamWithDeflate vtk_haru_HPDF_Stream_WriteToStreamWithDeflate
#define HPDF_Stream_WriteUChar vtk_haru_HPDF_Stream_WriteUChar
#define HPDF_Stream_WriteUInt vtk_haru_HPDF_Stream_WriteUInt
#define HPDF_Stream_Write vtk_haru_HPDF_Stream_Write
#define HPDF_String_Cmp vtk_haru_HPDF_String_Cmp
#define HPDF_String_Free vtk_haru_HPDF_String_Free
#define HPDF_String_New vtk_haru_HPDF_String_New
#define HPDF_String_SetValue vtk_haru_HPDF_String_SetValue
#define HPDF_String_Write vtk_haru_HPDF_String_Write
#define HPDF_StrLen vtk_haru_HPDF_StrLen
#define HPDF_StrStr vtk_haru_HPDF_StrStr
#define HPDF_TextAnnot_SetIcon vtk_haru_HPDF_TextAnnot_SetIcon
#define HPDF_TextAnnot_SetOpened vtk_haru_HPDF_TextAnnot_SetOpened
#define HPDF_TextMarkupAnnot_SetQuadPoints vtk_haru_HPDF_TextMarkupAnnot_SetQuadPoints
#define HPDF_ToBox vtk_haru_HPDF_ToBox
#define HPDF_ToPoint vtk_haru_HPDF_ToPoint
#define HPDF_ToRect vtk_haru_HPDF_ToRect
#define HPDF_TTFontDef_GetCharBBox vtk_haru_HPDF_TTFontDef_GetCharBBox
#define HPDF_TTFontDef_GetCharWidth vtk_haru_HPDF_TTFontDef_GetCharWidth
#define HPDF_TTFontDef_GetGidWidth vtk_haru_HPDF_TTFontDef_GetGidWidth
#define HPDF_TTFontDef_GetGlyphid vtk_haru_HPDF_TTFontDef_GetGlyphid
#define HPDF_TTFontDef_Load2 vtk_haru_HPDF_TTFontDef_Load2
#define HPDF_TTFontDef_Load vtk_haru_HPDF_TTFontDef_Load
#define HPDF_TTFontDef_New vtk_haru_HPDF_TTFontDef_New
#define HPDF_TTFontDef_SaveFontData vtk_haru_HPDF_TTFontDef_SaveFontData
#define HPDF_TTFontDef_SetTagName vtk_haru_HPDF_TTFontDef_SetTagName
#define HPDF_TTFont_New vtk_haru_HPDF_TTFont_New
#define HPDF_Type0Font_New vtk_haru_HPDF_Type0Font_New
#define HPDF_Type1FontDef_Duplicate vtk_haru_HPDF_Type1FontDef_Duplicate
#define HPDF_Type1FontDef_GetWidthByName vtk_haru_HPDF_Type1FontDef_GetWidthByName
#define HPDF_Type1FontDef_GetWidth vtk_haru_HPDF_Type1FontDef_GetWidth
#define HPDF_Type1FontDef_Load vtk_haru_HPDF_Type1FontDef_Load
#define HPDF_Type1FontDef_New vtk_haru_HPDF_Type1FontDef_New
#define HPDF_Type1FontDef_SetWidths vtk_haru_HPDF_Type1FontDef_SetWidths
#define HPDF_Type1Font_New vtk_haru_HPDF_Type1Font_New
#define HPDF_U3D_Add3DView vtk_haru_HPDF_U3D_Add3DView
#define HPDF_U3D_AddOnInstanciate vtk_haru_HPDF_U3D_AddOnInstanciate
#define HPDF_U3D_LoadU3DFromMem vtk_haru_HPDF_U3D_LoadU3DFromMem
#define HPDF_U3D_LoadU3D vtk_haru_HPDF_U3D_LoadU3D
#define HPDF_U3D_SetDefault3DView vtk_haru_HPDF_U3D_SetDefault3DView
#define HPDF_UInt16Swap vtk_haru_HPDF_UInt16Swap
#define HPDF_UnicodeToGryphName vtk_haru_HPDF_UnicodeToGryphName
#define HPDF_URILinkAnnot_New vtk_haru_HPDF_URILinkAnnot_New
#define HPDF_UseCNSEncodings vtk_haru_HPDF_UseCNSEncodings
#define HPDF_UseCNSFonts vtk_haru_HPDF_UseCNSFonts
#define HPDF_UseCNTEncodings vtk_haru_HPDF_UseCNTEncodings
#define HPDF_UseCNTFonts vtk_haru_HPDF_UseCNTFonts
#define HPDF_UseJPEncodings vtk_haru_HPDF_UseJPEncodings
#define HPDF_UseJPFonts vtk_haru_HPDF_UseJPFonts
#define HPDF_UseKREncodings vtk_haru_HPDF_UseKREncodings
#define HPDF_UseKRFonts vtk_haru_HPDF_UseKRFonts
#define HPDF_UseUTFEncodings vtk_haru_HPDF_UseUTFEncodings
#define HPDF_Xref_Add vtk_haru_HPDF_Xref_Add
#define HPDF_Xref_Free vtk_haru_HPDF_Xref_Free
#define HPDF_Xref_GetEntryByObjectId vtk_haru_HPDF_Xref_GetEntryByObjectId
#define HPDF_Xref_GetEntry vtk_haru_HPDF_Xref_GetEntry
#define HPDF_Xref_New vtk_haru_HPDF_Xref_New
#define HPDF_Xref_WriteToStream vtk_haru_HPDF_Xref_WriteToStream
#define TIFFFaxBlackCodes vtk_haru_TIFFFaxBlackCodes
#define TIFFFaxWhiteCodes vtk_haru_TIFFFaxWhiteCodes

#endif // vtk_haru_mangle_h