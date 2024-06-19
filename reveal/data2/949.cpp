TEST_F ( WebFrameTest , GetCanonicalUrlForSharingMultiple ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . Initialize ( ) ;
 WebLocalFrameImpl * frame = web_view_helper . LocalMainFrame ( ) ;
 FrameTestHelpers : : LoadHTMLString ( frame , R "( < head > < link rel = "canonical" href = "https://example.com/canonical1.html" > < link rel = "canonical" href = "https://example.com/canonical2.html" > < / head > ) ", ToKURL(" https : EXPECT_EQ ( WebURL ( ToKURL ( "https://example.com/canonical1.html" ) ) , frame -> GetDocument ( ) . CanonicalUrlForSharing ( ) ) ;
 }