# rohm-c014-dot-llc-full-bridge

- 原厂模型：[(C-014-DOT) DC-DC LLC Full-Bridge Converter (DOT247)_20260525.plecs](<plecs/(C-014-DOT) DC-DC LLC Full-Bridge Converter (DOT247)_20260525.plecs>)，SHA256 `b327fab7521540539e4f0b78751a6880572bc55aa9efefa46fbe4adeb30da05f`。
- 原厂完整仿真区间：0–0.2 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv) · [waveforms_003.csv](plecs/waveforms_003.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_c014_dot_llc_full_bridge.plecs](plecs/CaseSet_rohm_c014_dot_llc_full_bridge.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[netlist.md](pulse/netlist.md)。历史已转换输入；验收范围见 provenance.json。
- PULSE 原有默认仿真声明：`.TRAN T_END=0.20000000000000001 SAVE_DT=1u`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | V | R1 | Resistor voltage |
| CH002 | V | DOT247(HB)_A/FET_H/FET_H | Device voltage |
| CH003 | A | DOT247(HB)_A/Id_H | Measured current |
| CH004 | A | V_dc | Source current |
| CH005 | V | V_dc | Source voltage |
| CH006 | A | R1 | Resistor current |
| CH007 | V | Si(LV)-MOSFET_A/FET | Device voltage |
| CH008 | A | Si(LV)-MOSFET_A/FET | Device current |
| CH009 | A | Am14 | Measured current |
