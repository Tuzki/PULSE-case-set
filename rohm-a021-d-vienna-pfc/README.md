# rohm-a021-d-vienna-pfc

- 原厂模型：[(A-021-D) AC-DC 3-Phase Vienna PFC (Discrete)_20260525.plecs](<plecs/(A-021-D) AC-DC 3-Phase Vienna PFC (Discrete)_20260525.plecs>)，SHA256 `65f41691593b440ee891c59697922dd5ec416f45ae07862c37089fcd5e4350cf`。
- 原厂完整仿真区间：0–0.5 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv) · [waveforms_004.csv](plecs/waveforms_004.csv) · [waveforms_005.csv](plecs/waveforms_005.csv) · [waveforms_006.csv](plecs/waveforms_006.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_a021_d_vienna_pfc.plecs](plecs/CaseSet_rohm_a021_d_vienna_pfc.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。历史已转换输入；验收范围见 provenance.json。
- PULSE 原有默认仿真声明：`.TRAN T_END=0.5 SAVE_DT=1u`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH003 | V | V_ac1 | Source voltage |
| CH004 | V | V_ac2 | Source voltage |
| CH005 | V | V_ac3 | Source voltage |
| CH008 | A | V_ac1 | Source current |
| CH009 | A | V_ac2 | Source current |
| CH010 | A | V_ac3 | Source current |
| CH011 | A | Rload | Resistor current |
| CH001 | V | Rload | Resistor voltage |
| MOS_JUNCTION_TEMP_C | degC | SiC-MOSFET_A2 | Device junction temp |
| CH012 | V | SiC-MOSFET_A2 | Device voltage |
| CH013 | A | SiC-MOSFET_A2 | Device current |
| MOS_HEATSINK_TEMP_C | degC | Heat Sink | Temperature |
| DIODE_JUNCTION_TEMP_C | degC | SiC-SBD_A1 | Diode junction temperature (C) |
| CH014 | A | SiC-SBD_A1 | Diode current (A) |
| DIODE_HEATSINK_TEMP_C | degC | Heat Sink1 | Temperature |
| CH002 | A | L1 | Inductor current |
| CH006 | A | L2 | Inductor current |
| CH007 | A | L3 | Inductor current |

A021-D 的新增探针采集副本触发布局检查；本次改为把原有 Scope 的相同信号接到输出，并从既有 Iin1/Iin2/Iin3 探针各增加纯观测分支。14 个电气通道均保留，另外保留原 Scope 的 4 个温度通道；原有电气、控制和探针组件不变，原有信号连接关系已逐项核对。
