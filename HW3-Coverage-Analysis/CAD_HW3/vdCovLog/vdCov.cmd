gui_exclusion -set_force true
gui_assert_mode -mode flat
gui_class_mode -mode hier
gui_excl_mgr_flat_list -on  0
gui_covdetail_select -id  CovDetail.1   -name   Line
verdiWindowWorkMode -win $_vdCoverage_1 -coverageAnalysis
gui_open_cov  -hier simv.vdb -testdir {} -test {simv/test} -merge MergedTest -db_max_tests 10 -fsm transition
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test  -column {} 
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test.cc
gui_list_collapse -id  CoverageTable.1   -list {covtblInstancesList} test.cc
gui_covtable_show -show  { Design Hierarchy } -id  CoverageTable.1  -test  MergedTest
gui_reload_cov 
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test.cc
gui_reload_cov 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test   }
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test
gui_list_expand -id CoverageTable.1   test
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test  -column {} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test  test.cc   }
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test.cc
gui_list_expand -id CoverageTable.1   test.cc
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc  -column {} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test.cc  test.cc.r1   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc.r1  -column {Toggle} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test.cc.r1  test.cc.c1   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc.c1  -column {Line} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test.cc.c1  test.cc.r1   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc.r1  -column {Toggle} 
gui_covdetail_select -id  CovDetail.1   -name   FSM
gui_covdetail_select -id  CovDetail.1   -name   Toggle
gui_covdetail_select -id  CovDetail.1   -name   Line
gui_covdetail_select -id  CovDetail.1   -name   Toggle
gui_reload_cov 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test   }
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test
gui_list_expand -id CoverageTable.1   test
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test  -column {} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test  test.cc   }
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test.cc
gui_list_expand -id CoverageTable.1   test.cc
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc  -column {} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test.cc  test.cc.c1   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc.c1  -column {Line} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test.cc.c1  test.cc.a1   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc.a1  -column {Toggle} 
gui_reload_cov 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test   }
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test
gui_list_expand -id CoverageTable.1   test
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test  -column {FSM} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test  test.cc   }
gui_list_expand -id  CoverageTable.1   -list {covtblInstancesList} test.cc
gui_list_expand -id CoverageTable.1   test.cc
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc  -column {FSM} 
gui_list_select -id CoverageTable.1 -list covtblInstancesList { test.cc  test.cc.c1   }
gui_list_action -id  CoverageTable.1 -list {covtblInstancesList} test.cc.c1  -column {FSM} 
gui_list_action -id  CovDetail.1 -list {fsmnames} current_state
gui_list_action -id  CovDetail.1 -list {fsmnames} current_state
gui_covtable_show -show  { Design Hierarchy } -id  CoverageTable.1  -test  MergedTest
gui_src_highlight_item -id CovSrc.1 -lfrom 120 -idxfrom 9 -fileIdFrom 0 -lto 120 -idxto 22 -fileIdTo 0 -selection {current_state} -selectionId 0 -replace 0
gui_cov_src_double_click -id CovSrc.1 -line 120 -col 16 -insert 0 -file /edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/a111204_cpu.v
gui_src_highlight_item -id CovSrc.1 -lfrom 120 -idxfrom 9 -fileIdFrom 0 -lto 120 -idxto 22 -fileIdTo 0 -selection {current_state} -selectionId 0 -replace 0
gui_src_highlight_item -id CovSrc.1 -lfrom 120 -idxfrom 9 -fileIdFrom 0 -lto 120 -idxto 22 -fileIdTo 0 -selection {current_state} -selectionId 0 -replace 0
gui_cov_src_double_click -id CovSrc.1 -line 120 -col 16 -insert 0 -file /edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/a111204_cpu.v
gui_src_highlight_item -id CovSrc.1 -lfrom 120 -idxfrom 9 -fileIdFrom 0 -lto 120 -idxto 22 -fileIdTo 0 -selection {current_state} -selectionId 0 -replace 0
gui_list_action -id  CovDetail.1 -list {fsmnames} current_state
gui_tbl_select -id CovDetail.1   { {3,0,3,0} }
gui_list_action -id   CovSrc.1  -list {fsm list}  current_state#ST_3->ST_0
gui_tbl_select -id CovDetail.1   { {3,1,3,1} }
gui_list_action -id   CovSrc.1  -list {fsm list}  current_state#ST_3->ST_1
gui_tbl_select -id CovDetail.1   { {3,0,3,0} }
gui_list_action -id   CovSrc.1  -list {fsm list}  current_state#ST_3->ST_0
gui_tbl_select -id CovDetail.1   { {3,1,3,1} }
gui_list_action -id   CovSrc.1  -list {fsm list}  current_state#ST_3->ST_1
gui_reload_cov 
