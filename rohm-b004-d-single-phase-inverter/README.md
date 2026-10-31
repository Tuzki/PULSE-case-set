# rohm-b004-d-single-phase-inverter

- 原厂模型：[(B-004-D) DC-AC Single-phase 2-Level Full-Bridge Inverter (Discrete)_20260525.plecs](<plecs/(B-004-D) DC-AC Single-phase 2-Level Full-Bridge Inverter (Discrete)_20260525.plecs>)，SHA256 `ade99cec084d07ec3cb5284a33373a1cadcd630d96b94dbce653c838b6a6f39c`。
- 原厂完整仿真区间：0–0.5 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv) · [waveforms_004.csv](plecs/waveforms_004.csv) · [waveforms_005.csv](plecs/waveforms_005.csv) · [waveforms_006.csv](plecs/waveforms_006.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_b004_d_single_phase_inverter.plecs](plecs/CaseSet_rohm_b004_d_single_phase_inverter.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。历史已转换输入；验收范围见 provenance.json。
- PULSE 原有默认仿真声明：`.TRAN T_END=.5 SAVE_DT=.000001`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | V | Vin | Source voltage |
| CH002 | A | Am2 | Measured current |
| CH003 | A | Am3 | Measured current |
| CH004 | A | Vin | Source current |
| CH005 | A | Rload | Resistor current |
| CH006 | V | Vout | Measured voltage |
| CH007 | V | SiC_MOSFET_1_HS/FET | Device voltage |
| CH008 | V | SiC_MOSFET_1_LS/FET | Device voltage |
| CH009 | A | SiC_MOSFET_1_HS/FET | Device current |
| CH010 | A | SiC_MOSFET_1_LS/FET | Device current |
