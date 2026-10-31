# rohm-c019-dot-phase-shift-full-bridge

- 原厂模型：[(C-019-DOT) DC-DC Phase-Shift Full-Bridge Converter (DOT247)_20260525.plecs](<plecs/(C-019-DOT) DC-DC Phase-Shift Full-Bridge Converter (DOT247)_20260525.plecs>)，SHA256 `1408a8793c8c04bd633a2e470abce3a6fff4f42188da670b5fca8925cb4f87c7`。
- 原厂完整仿真区间：0–0.15 s。导出状态：**COMPLETED**。
- CSV：[waveforms_001.csv](plecs/waveforms_001.csv) · [waveforms_002.csv](plecs/waveforms_002.csv)。采样间隔 1 µs，数值以 17 位有效数字输出；按文件序号连接各段，段间没有重复行。此均匀输出网格不是 PLECS 内部积分步长，也不保证捕获所有开关边沿。
- PLECS 观测模型：[CaseSet_rohm_c019_dot_phase_shift_full_bridge.plecs](plecs/CaseSet_rohm_c019_dot_phase_shift_full_bridge.plecs)；仅调整观测输出，保留原厂物理和控制设置。
- PULSE：[缺口说明](pulse/README.md)。尚无已转换网表；未拿 D 版冒充 DOT 版。
- PULSE 原有默认仿真声明：`无网表`。未为本次打包修改窗口或控制逻辑。
- 原始下载资料在 `source/` 内平铺；模型运行所需器件 XML 位于 `plecs/*_plecs/`，这是 PLECS 的配套资源目录。
- 逐文件来源、哈希、导出终点和控制条件见 [provenance.json](provenance.json)。

本仓库收录输入和 PLECS 参考数据，不将 PLECS 全时长完成视为 PULSE 全时长精度通过。

## CSV 通道

| CSV 列 | 单位 | PLECS 器件路径 | 信号 |
|---|---|---|---|
| time_s | s | 仿真时间 | 时间 |
| CH001 | A | Lr | Inductor current |
| CH002 | A | DOT247(HB)_A1/Id_H | Measured current |
| CH003 | A | DOT247(HB)_A2/Id_L | Measured current |
| CH004 | V | Vdc | Source voltage |
| CH005 | V | Rload | Resistor voltage |
| CH006 | A | Rload | Resistor current |
| CH007 | A | Vdc | Source current |
| CH008 | A | SiC-SBD_A1/D1 | Diode current |
| CH009 | A | SiC-SBD_A2/D1 | Diode current |
