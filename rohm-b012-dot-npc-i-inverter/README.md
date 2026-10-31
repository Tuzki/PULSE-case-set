# rohm-b012-dot-npc-i-inverter

- 原厂模型：[(B-012-DOT) DC-AC 3-phase 3-Level NPC-Type-I Inverter (DOT247)_20260525.plecs](<plecs/(B-012-DOT) DC-AC 3-phase 3-Level NPC-Type-I Inverter (DOT247)_20260525.plecs>)，SHA256 `aa9371cf82d17fca823b0575b8ec604029c3f05042ed8e395411dd0dd9a1d643`。
- 原厂完整仿真区间：0–0.5 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv) · [waveforms_004.csv](plecs/waveforms_004.csv) · [waveforms_005.csv](plecs/waveforms_005.csv) · [waveforms_006.csv](plecs/waveforms_006.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_b012_dot_npc_i_inverter.plecs](plecs/CaseSet_rohm_b012_dot_npc_i_inverter.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。原 C 候选；门极边界语义待查；不采用 DSH 提前关断版本。
- PULSE 原有默认仿真声明：`.TRAN T_END=0.020003 SAVE_DT=0.000001`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | V | VIN | Measured voltage |
| CH002 | A | Vin/2 | Source current |
| CH003 | A | Vin/2' | Source current |
| CH004 | V | 3ph Meter | Measured voltage[0] |
| CH005 | V | 3ph Meter | Measured voltage[1] |
| CH006 | V | 3ph Meter | Measured voltage[2] |
| CH007 | A | 3ph Meter | Measured current[0] |
| CH008 | A | 3ph Meter | Measured current[1] |
| CH009 | A | 3ph Meter | Measured current[2] |
| CH010 | V | DOT247(HB)_A/FET_L/FET_L | Device voltage |
| CH011 | V | DOT247(HB)_A/FET_H/FET_H | Device voltage |
| CH012 | A | DOT247(HB)_A/Id_L | Measured current |
| CH013 | A | DOT247(HB)_A/Id_H | Measured current |
| CH014 | V | DOT247(HB)_A2/FET_L/FET_L | Device voltage |
| CH015 | V | DOT247(HB)_A2/FET_H/FET_H | Device voltage |
| CH016 | A | DOT247(HB)_A2/Id_H | Measured current |
| CH017 | A | DOT247(HB)_A2/Id_L | Measured current |
| CH018 | V | DOT247(HB)_A1/FET_H/FET_H | Device voltage |
| CH019 | V | DOT247(HB)_A1/FET_L/FET_L | Device voltage |
| CH020 | A | DOT247(HB)_A1/Id_H | Measured current |
| CH021 | A | DOT247(HB)_A1/Id_L | Measured current |
