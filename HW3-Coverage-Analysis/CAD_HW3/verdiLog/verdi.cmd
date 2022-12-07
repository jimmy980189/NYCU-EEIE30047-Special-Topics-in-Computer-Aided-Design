debImport \
          "/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu_bug.v" \
          -path \
          {/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3}
wvCreateWindow
wvSetPosition -win $_nWave2 {("G1" 0)}
wvOpenFile -win $_nWave2 \
           {/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu.vcd.fsdb}
wvGetSignalOpen -win $_nWave2
wvGetSignalSetScope -win $_nWave2 "/test"
wvSetPosition -win $_nWave2 {("G1" 2)}
wvSetPosition -win $_nWave2 {("G1" 2)}
wvAddSignal -win $_nWave2 -clear
wvAddSignal -win $_nWave2 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
}
wvAddSignal -win $_nWave2 -group {"G2" \
}
wvSelectSignal -win $_nWave2 {( "G1" 1 2 )} 
wvSetPosition -win $_nWave2 {("G1" 2)}
wvGetSignalClose -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvSelectSignal -win $_nWave2 {( "G1" 1 )} 
wvSelectSignal -win $_nWave2 {( "G1" 1 )} 
wvSetRadix -win $_nWave2 -format Bin
wvZoomIn -win $_nWave2
wvSetCursor -win $_nWave2 240.047390 -snap {("G1" 1)}
wvSelectSignal -win $_nWave2 {( "G1" 2 )} 
wvGetSignalOpen -win $_nWave2
wvGetSignalSetScope -win $_nWave2 "/test"
wvGetSignalSetScope -win $_nWave2 "/test"
wvGetSignalSetScope -win $_nWave2 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave2 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave2 "/test/cc"
wvSetPosition -win $_nWave2 {("G1" 7)}
wvSetPosition -win $_nWave2 {("G1" 7)}
wvAddSignal -win $_nWave2 -clear
wvAddSignal -win $_nWave2 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/addr\[3:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_mem} \
{/test/cc/w_reg_c} \
{/test/cc/write_data\[7:0\]} \
}
wvAddSignal -win $_nWave2 -group {"G2" \
}
wvSelectSignal -win $_nWave2 {( "G1" 3 4 5 6 7 )} 
wvSetPosition -win $_nWave2 {("G1" 7)}
wvSetPosition -win $_nWave2 {("G1" 7)}
wvSetPosition -win $_nWave2 {("G1" 7)}
wvAddSignal -win $_nWave2 -clear
wvAddSignal -win $_nWave2 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/addr\[3:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_mem} \
{/test/cc/w_reg_c} \
{/test/cc/write_data\[7:0\]} \
}
wvAddSignal -win $_nWave2 -group {"G2" \
}
wvSelectSignal -win $_nWave2 {( "G1" 3 4 5 6 7 )} 
wvSetPosition -win $_nWave2 {("G1" 7)}
wvGetSignalClose -win $_nWave2
wvSelectSignal -win $_nWave2 {( "G1" 3 4 5 6 7 )} 
wvSetRadix -win $_nWave2 -format Bin
wvSetCursor -win $_nWave2 255.285602 -snap {("G1" 5)}
wvSetCursor -win $_nWave2 259.946702 -snap {("G1" 1)}
wvSetCursor -win $_nWave2 265.145622 -snap {("G1" 5)}
wvSetCursor -win $_nWave2 240.226663 -snap {("G1" 1)}
wvSetCursor -win $_nWave2 199.352400 -snap {("G1" 1)}
wvSetCursor -win $_nWave2 240.608994 -snap {("G1" 1)}
wvSetCursor -win $_nWave2 305.008055 -snap {("G1" 6)}
wvSetCursor -win $_nWave2 265.030157 -snap {("G1" 5)}
wvSetCursor -win $_nWave2 265.030157 -snap {("G1" 5)}
srcDeselectAll -win $_nTrace1
srcDeselectAll -win $_nTrace1
srcSelect -signal "w_mem" -line 35 -pos 1 -win $_nTrace1
srcAction -pos 34 17 1 -win $_nTrace1 -name "w_mem" -ctrlKey off
nsMsgSelect -range {0 15-15}
nsMsgAction -tab trace -index {0 15}
nsMsgSelect -range {0 9-9}
nsMsgAction -tab trace -index {0 9}
nsMsgSelect -range {0 9-9}
nsMsgSelect -range {0 8-8}
nsMsgAction -tab trace -index {0 8}
nsMsgSelect -range {0 8-8}
verdiDockWidgetSetCurTab -dock windowDock_nWave_2
verdiDockWidgetSetCurTab -dock windowDock_OneSearch
verdiDockWidgetSetCurTab -dock widgetDock_<Message>
nsMsgSelect -range {0 7-7}
nsMsgAction -tab trace -index {0 7}
nsMsgSelect -range {0 7-7}
nsMsgSelect -range {0 11-11}
nsMsgAction -tab trace -index {0 11}
nsMsgSelect -range {0 11-11}
nsMsgSelect -range {0 8-8}
nsMsgAction -tab trace -index {0 8}
nsMsgSelect -range {0 8-8}
nsMsgSelect -range {0 9-9}
nsMsgAction -tab trace -index {0 9}
nsMsgSelect -range {0 9-9}
nsMsgSelect -range {0 0-0}
verdiDockWidgetSetCurTab -dock windowDock_nWave_2
wvDisplayGridCount -win $_nWave2 -off
wvGetSignalClose -win $_nWave2
wvReloadFile -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomIn -win $_nWave2
wvZoomIn -win $_nWave2
srcHBSelect "cpu.r1" -win $_nTrace1
srcSetScope -win $_nTrace1 "cpu.r1" -delim "."
srcHBSelect "cpu.r1" -win $_nTrace1
srcDeselectAll -win $_nTrace1
srcSelect -signal "data_out" -line 14 -pos 1 -win $_nTrace1
srcAction -pos 13 2 3 -win $_nTrace1 -name "data_out" -ctrlKey off
verdiDockWidgetSetCurTab -dock windowDock_nWave_2
wvGetSignalOpen -win $_nWave2
wvGetSignalSetScope -win $_nWave2 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave2 "/test/cc/r1"
wvSetPosition -win $_nWave2 {("G1" 8)}
wvSetPosition -win $_nWave2 {("G1" 8)}
wvAddSignal -win $_nWave2 -clear
wvAddSignal -win $_nWave2 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/addr\[3:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_mem} \
{/test/cc/w_reg_c} \
{/test/cc/write_data\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
}
wvAddSignal -win $_nWave2 -group {"G2" \
}
wvSelectSignal -win $_nWave2 {( "G1" 8 )} 
wvSetPosition -win $_nWave2 {("G1" 8)}
wvSetPosition -win $_nWave2 {("G1" 8)}
wvSetPosition -win $_nWave2 {("G1" 8)}
wvAddSignal -win $_nWave2 -clear
wvAddSignal -win $_nWave2 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/addr\[3:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_mem} \
{/test/cc/w_reg_c} \
{/test/cc/write_data\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
}
wvAddSignal -win $_nWave2 -group {"G2" \
}
wvSelectSignal -win $_nWave2 {( "G1" 8 )} 
wvSetPosition -win $_nWave2 {("G1" 8)}
wvGetSignalClose -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvSetCursor -win $_nWave2 294.413016 -snap {("G1" 8)}
wvZoomIn -win $_nWave2
wvSelectSignal -win $_nWave2 {( "G1" 7 )} 
wvSetCursor -win $_nWave2 294.251670 -snap {("G1" 8)}
wvSetCursor -win $_nWave2 299.271316 -snap {("G1" 8)}
wvSelectSignal -win $_nWave2 {( "G1" 8 )} 
wvSelectSignal -win $_nWave2 {( "G1" 8 )} 
wvSelectSignal -win $_nWave2 {( "G1" 8 )} 
wvSetRadix -win $_nWave2 -format Bin
wvZoomIn -win $_nWave2
wvDisplayGridCount -win $_nWave2 -off
wvGetSignalClose -win $_nWave2
wvReloadFile -win $_nWave2
wvSetCursor -win $_nWave2 319.066740 -snap {("G2" 0)}
wvDisplayGridCount -win $_nWave2 -off
wvGetSignalClose -win $_nWave2
wvReloadFile -win $_nWave2
wvZoomOut -win $_nWave2
verdiWindowResize -win $_Verdi_1 "10" "0" "1281" "842"
verdiWindowResize -win $_Verdi_1 "10" "0" "1326" "867"
wvSelectSignal -win $_nWave2 {( "G1" 2 )} 
wvGetSignalOpen -win $_nWave2
wvSetPosition -win $_nWave2 {("G1" 9)}
wvSetPosition -win $_nWave2 {("G1" 9)}
wvAddSignal -win $_nWave2 -clear
wvAddSignal -win $_nWave2 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/addr\[3:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_mem} \
{/test/cc/w_reg_c} \
{/test/cc/write_data\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/out\[7:0\]} \
}
wvAddSignal -win $_nWave2 -group {"G2" \
}
wvSelectSignal -win $_nWave2 {( "G1" 9 )} 
wvSetPosition -win $_nWave2 {("G1" 9)}
wvGetSignalClose -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomOut -win $_nWave2
wvZoomIn -win $_nWave2
wvSetCursor -win $_nWave2 191.777753 -snap {("G1" 0)}
wvSetCursor -win $_nWave2 193.707269 -snap {("G1" 1)}
wvSetCursor -win $_nWave2 187.966960 -snap {("G1" 1)}
wvSetCursor -win $_nWave2 185.989537 -snap {("G1" 7)}
wvSetCursor -win $_nWave2 195.476322 -snap {("G1" 4)}
wvSetCursor -win $_nWave2 257.060022 -snap {("G1" 4)}
wvSelectSignal -win $_nWave2 {( "G1" 4 )} 
wvSelectSignal -win $_nWave2 {( "G1" 4 )} 
wvSetRadix -win $_nWave2 -format UDec
wvSetRadix -win $_nWave2 -2Com
wvSelectSignal -win $_nWave2 {( "G1" 4 )} 
wvSetRadix -win $_nWave2 -format Bin
wvSetRadix -win $_nWave2 -Unsigned
wvSetCursor -win $_nWave2 281.661344 -snap {("G1" 1)}
wvZoomOut -win $_nWave2
wvZoomIn -win $_nWave2
wvSetCursor -win $_nWave2 179.300684 -snap {("G1" 1)}
wvZoomOut -win $_nWave2
wvZoomIn -win $_nWave2
wvSetCursor -win $_nWave2 46.012511 -snap {("G2" 0)}
wvDisplayGridCount -win $_nWave2 -off
wvGetSignalClose -win $_nWave2
wvReloadFile -win $_nWave2
wvTpfCloseForm -win $_nWave2
wvGetSignalClose -win $_nWave2
wvCloseWindow -win $_nWave2
wvCreateWindow
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvSetPosition -win $_nWave3 {("G1" 2)}
wvSetPosition -win $_nWave3 {("G1" 2)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 1 2 )} 
wvSetPosition -win $_nWave3 {("G1" 2)}
wvGetSignalClose -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomIn -win $_nWave3
wvZoomIn -win $_nWave3
wvSetCursor -win $_nWave3 164.049009 -snap {("G2" 0)}
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvGetSignalSetScope -win $_nWave3 "/test"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvSetPosition -win $_nWave3 {("G1" 4)}
wvSetPosition -win $_nWave3 {("G1" 4)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 3 4 )} 
wvSetPosition -win $_nWave3 {("G1" 4)}
wvGetSignalClose -win $_nWave3
wvZoomIn -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomOut -win $_nWave3
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvSetPosition -win $_nWave3 {("G1" 6)}
wvSetPosition -win $_nWave3 {("G1" 6)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 5 6 )} 
wvSetPosition -win $_nWave3 {("G1" 6)}
wvGetSignalClose -win $_nWave3
wvZoomIn -win $_nWave3
wvSetCursor -win $_nWave3 132.975771 -snap {("G2" 0)}
wvDisplayGridCount -win $_nWave3 -off
wvGetSignalClose -win $_nWave3
wvReloadFile -win $_nWave3
wvSetCursor -win $_nWave3 51.614537 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 164.330396 -snap {("G2" 0)}
wvDisplayGridCount -win $_nWave3 -off
wvGetSignalClose -win $_nWave3
wvReloadFile -win $_nWave3
wvSetCursor -win $_nWave3 44.861233 -snap {("G1" 1)}
wvConvertFile -win $_nWave3 -o \
           "/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu.vcd.fsdb" \
           "/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu.vcd"
wvOpenFile -win $_nWave3 \
           {/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu.vcd.fsdb}
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvSetPosition -win $_nWave3 {("G1" 6)}
wvSetPosition -win $_nWave3 {("G1" 6)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSetPosition -win $_nWave3 {("G1" 6)}
wvGetSignalClose -win $_nWave3
wvGetSignalClose -win $_nWave3
wvGetSignalClose -win $_nWave3
wvSelectGroup -win $_nWave3 {G1}
wvSelectGroup -win $_nWave3 {G2}
wvDisplayGridCount -win $_nWave3 -off
wvGetSignalClose -win $_nWave3
wvConvertFile -win $_nWave3 -o \
           "/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu.vcd.fsdb" \
           "/edahome/course/2022CAD/2022CAD021/NYCU-EEIE30047-Special-Topics-in-Computer-Aided-Design/HW3-Coverage-Analysis/CAD_HW3/cpu.vcd"
wvReloadFile -win $_nWave3
wvZoomOut -win $_nWave3
wvZoomIn -win $_nWave3
wvSetCursor -win $_nWave3 200.267621 -snap {("G1" 1)}
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test/cc/a1"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalClose -win $_nWave3
wvSelectSignal -win $_nWave3 {( "G1" 4 )} 
wvZoomIn -win $_nWave3
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvSetPosition -win $_nWave3 {("G1" 7)}
wvSetPosition -win $_nWave3 {("G1" 7)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
{/test/cc/r1/w_mem} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 7 )} 
wvSetPosition -win $_nWave3 {("G1" 7)}
wvGetSignalClose -win $_nWave3
wvSetCursor -win $_nWave3 210.730204 -snap {("G1" 0)}
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvSetPosition -win $_nWave3 {("G1" 8)}
wvSetPosition -win $_nWave3 {("G1" 8)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
{/test/cc/r1/w_mem} \
{/test/cc/r1/address\[3:0\]} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 8 )} 
wvSetPosition -win $_nWave3 {("G1" 8)}
wvGetSignalSetScope -win $_nWave3 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave3 "/test/cc/a1"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvSetPosition -win $_nWave3 {("G1" 9)}
wvSetPosition -win $_nWave3 {("G1" 9)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
{/test/cc/r1/w_mem} \
{/test/cc/r1/address\[3:0\]} \
{/test/cc/write_data\[7:0\]} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 9 )} 
wvSetPosition -win $_nWave3 {("G1" 9)}
wvSetPosition -win $_nWave3 {("G1" 9)}
wvSetPosition -win $_nWave3 {("G1" 9)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
{/test/cc/r1/w_mem} \
{/test/cc/r1/address\[3:0\]} \
{/test/cc/write_data\[7:0\]} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 9 )} 
wvSetPosition -win $_nWave3 {("G1" 9)}
wvGetSignalClose -win $_nWave3
wvSelectSignal -win $_nWave3 {( "G1" 8 )} 
wvSelectSignal -win $_nWave3 {( "G1" 9 )} 
wvSelectSignal -win $_nWave3 {( "G1" 8 )} 
wvSelectSignal -win $_nWave3 {( "G1" 8 9 )} 
wvSelectSignal -win $_nWave3 {( "G1" 8 9 )} 
wvSetRadix -win $_nWave3 -format Bin
wvZoomOut -win $_nWave3
wvSetCursor -win $_nWave3 254.908068 -snap {("G1" 6)}
wvSetCursor -win $_nWave3 204.740667 -snap {("G1" 6)}
wvSetCursor -win $_nWave3 279.670182 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 199.595292 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 240.115116 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 280.152561 -snap {("G1" 1)}
wvSelectSignal -win $_nWave3 {( "G1" 6 )} 
wvGetSignalOpen -win $_nWave3
wvGetSignalSetScope -win $_nWave3 "/test"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvGetSignalSetScope -win $_nWave3 "/test/cc/r1"
wvGetSignalSetScope -win $_nWave3 "/test/cc"
wvSetPosition -win $_nWave3 {("G1" 13)}
wvSetPosition -win $_nWave3 {("G1" 13)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
{/test/cc/r1/w_mem} \
{/test/cc/r1/address\[3:0\]} \
{/test/cc/write_data\[7:0\]} \
{/test/cc/reg_a\[7:0\]} \
{/test/cc/reg_b\[7:0\]} \
{/test/cc/w_reg_a} \
{/test/cc/w_reg_b} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 10 11 12 13 )} 
wvSetPosition -win $_nWave3 {("G1" 13)}
wvSetPosition -win $_nWave3 {("G1" 13)}
wvSetPosition -win $_nWave3 {("G1" 13)}
wvAddSignal -win $_nWave3 -clear
wvAddSignal -win $_nWave3 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/r1/data_in\[7:0\]} \
{/test/cc/r1/data_out\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_c} \
{/test/cc/r1/w_mem} \
{/test/cc/r1/address\[3:0\]} \
{/test/cc/write_data\[7:0\]} \
{/test/cc/reg_a\[7:0\]} \
{/test/cc/reg_b\[7:0\]} \
{/test/cc/w_reg_a} \
{/test/cc/w_reg_b} \
}
wvAddSignal -win $_nWave3 -group {"G2" \
}
wvSelectSignal -win $_nWave3 {( "G1" 10 11 12 13 )} 
wvSetPosition -win $_nWave3 {("G1" 13)}
wvGetSignalClose -win $_nWave3
wvSetPosition -win $_nWave3 {("G1" 10)}
wvSetPosition -win $_nWave3 {("G1" 6)}
wvSetPosition -win $_nWave3 {("G1" 5)}
wvMoveSelected -win $_nWave3
wvSetPosition -win $_nWave3 {("G1" 5)}
wvSetPosition -win $_nWave3 {("G1" 9)}
wvSelectSignal -win $_nWave3 {( "G1" 10 )} 
wvSelectSignal -win $_nWave3 {( "G1" 5 )} 
wvSetPosition -win $_nWave3 {("G1" 5)}
wvSetPosition -win $_nWave3 {("G1" 6)}
wvSetPosition -win $_nWave3 {("G1" 7)}
wvMoveSelected -win $_nWave3
wvSetPosition -win $_nWave3 {("G1" 7)}
wvSelectSignal -win $_nWave3 {( "G1" 5 )} 
wvSelectSignal -win $_nWave3 {( "G1" 6 )} 
wvSelectSignal -win $_nWave3 {( "G1" 6 )} 
wvSetRadix -win $_nWave3 -format Bin
wvSelectSignal -win $_nWave3 {( "G1" 5 )} 
wvSelectSignal -win $_nWave3 {( "G1" 5 )} 
wvSetRadix -win $_nWave3 -format Bin
wvSelectSignal -win $_nWave3 {( "G1" 9 )} 
wvSetCursor -win $_nWave3 199.756085 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 184.963134 -snap {("G1" 9)}
wvSetCursor -win $_nWave3 204.740667 -snap {("G1" 9)}
wvZoomIn -win $_nWave3
wvSetCursor -win $_nWave3 224.960380 -snap {("G1" 11)}
wvSetCursor -win $_nWave3 199.715887 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 239.512142 -snap {("G1" 1)}
wvSetCursor -win $_nWave3 255.109059 -snap {("G1" 10)}
wvSelectSignal -win $_nWave3 {( "G1" 10 )} 
wvSetCursor -win $_nWave3 264.997825 -snap {("G1" 8)}
wvZoomOut -win $_nWave3
wvSetCursor -win $_nWave3 284.976350 -snap {("G1" 10)}
wvSetCursor -win $_nWave3 304.914676 -snap {("G1" 11)}
wvSetCursor -win $_nWave3 295.106305 -snap {("G1" 7)}
wvSelectSignal -win $_nWave3 {( "G1" 7 )} 
wvSetRadix -win $_nWave3 -2Com
wvSelectSignal -win $_nWave3 {( "G1" 7 )} 
wvSetRadix -win $_nWave3 -format UDec
wvSelectSignal -win $_nWave3 {( "G1" 7 )} 
wvSetRadix -win $_nWave3 -format Bin
wvSetRadix -win $_nWave3 -Unsigned
wvSetCursor -win $_nWave3 214.709830 -snap {("G1" 7)}
wvSetCursor -win $_nWave3 214.709830 -snap {("G1" 7)}
wvTpfCloseForm -win $_nWave3
wvGetSignalClose -win $_nWave3
wvCloseWindow -win $_nWave3
wvCreateWindow
wvGetSignalOpen -win $_nWave4
wvGetSignalSetScope -win $_nWave4 "/test"
wvSetPosition -win $_nWave4 {("G1" 2)}
wvSetPosition -win $_nWave4 {("G1" 2)}
wvAddSignal -win $_nWave4 -clear
wvAddSignal -win $_nWave4 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
}
wvAddSignal -win $_nWave4 -group {"G2" \
}
wvSelectSignal -win $_nWave4 {( "G1" 1 2 )} 
wvSetPosition -win $_nWave4 {("G1" 2)}
wvGetSignalSetScope -win $_nWave4 "/test/cc/c1"
wvGetSignalSetScope -win $_nWave4 "/test/cc/a1"
wvGetSignalSetScope -win $_nWave4 "/test/cc"
wvSetPosition -win $_nWave4 {("G1" 6)}
wvSetPosition -win $_nWave4 {("G1" 6)}
wvAddSignal -win $_nWave4 -clear
wvAddSignal -win $_nWave4 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/reg_a\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_a} \
{/test/cc/w_reg_c} \
}
wvAddSignal -win $_nWave4 -group {"G2" \
}
wvSelectSignal -win $_nWave4 {( "G1" 3 4 5 6 )} 
wvSetPosition -win $_nWave4 {("G1" 6)}
wvSetPosition -win $_nWave4 {("G1" 6)}
wvSetPosition -win $_nWave4 {("G1" 6)}
wvAddSignal -win $_nWave4 -clear
wvAddSignal -win $_nWave4 -group {"G1" \
{/test/in\[7:0\]} \
{/test/out\[7:0\]} \
{/test/cc/reg_a\[7:0\]} \
{/test/cc/reg_c\[7:0\]} \
{/test/cc/w_reg_a} \
{/test/cc/w_reg_c} \
}
wvAddSignal -win $_nWave4 -group {"G2" \
}
wvSelectSignal -win $_nWave4 {( "G1" 3 4 5 6 )} 
wvSetPosition -win $_nWave4 {("G1" 6)}
wvGetSignalClose -win $_nWave4
wvZoomOut -win $_nWave4
wvZoomOut -win $_nWave4
wvZoomOut -win $_nWave4
wvZoomOut -win $_nWave4
wvZoomOut -win $_nWave4
wvSetCursor -win $_nWave4 344.912775 -snap {("G1" 3)}
debExit
