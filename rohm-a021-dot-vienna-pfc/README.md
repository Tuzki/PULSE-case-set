# rohm-a021-dot-vienna-pfc

- 原厂模型：[(A-021-DOT) AC-DC 3-Phase Vienna PFC (DOT247)_20260525.plecs](<plecs/(A-021-DOT) AC-DC 3-Phase Vienna PFC (DOT247)_20260525.plecs>)，SHA256 `5b41f705acd10170be056174aa1b9db0e5aa4b097dbbc55b61a391e812c19440`。
- 原厂完整仿真区间：0–0.5 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv) · [waveforms_004.csv](plecs/waveforms_004.csv) · [waveforms_005.csv](plecs/waveforms_005.csv) · [waveforms_006.csv](plecs/waveforms_006.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_a021_dot_vienna_pfc.plecs](plecs/CaseSet_rohm_a021_dot_vienna_pfc.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。历史已转换输入；验收范围见 provenance.json。
- PULSE 原有默认仿真声明：`.TRAN T_END=0.5 SAVE_DT=1u`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | V | Rload | Resistor voltage |
| CH002 | A | L1 | Inductor current |
| CH003 | V | V_ac1 | Source voltage |
| CH004 | V | V_ac2 | Source voltage |
| CH005 | V | V_ac3 | Source voltage |
| CH006 | A | L2 | Inductor current |
| CH007 | A | L3 | Inductor current |
| CH008 | A | V_ac1 | Source current |
| CH009 | A | V_ac2 | Source current |
| CH010 | A | V_ac3 | Source current |
| CH011 | A | Rload | Resistor current |
| CH012 | V | DOT247(CS)_A1/FET_1/FET_1 | Device voltage |
| CH013 | A | DOT247(CS)_A1/Id_1 | Measured current |
| CH014 | A | SiC-SBD_A1/D1 | Diode current |
