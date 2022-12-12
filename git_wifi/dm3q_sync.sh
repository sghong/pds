#!/bin/bash
#SS.SOS.Rel.Waipio.GS22
#SS.HMT.Eval
#SS.SOS.Rel.R9
#SS.SOS.Rel.Palima.Q4
#SS.SOS.Rel.Lahaina
#SS.TOS.DM3Q


git clone https://github.qualcomm.com/SS-release-management/qcacld-3.0_S_OS/ qcacld-3.0
cd qcacld-3.0;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/qca-wifi-host-cmn_S_OS/ qca-wifi-host-cmn
cd qca-wifi-host-cmn;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/fw-api_S_OS/ fw-api
cd fw-api;git checkout $1;cd ..

git clone https://github.qualcomm.com/SS-release-management/platform/ platform
cd platform;git checkout $1;cd ..

git clone https://github.qualcomm.com/SS-release-management/INI_SS INI_SS

git clone https://github.qualcomm.com/SS-release-management/SS_CNSS2_OEMSS/ SS_CNSS2_OEMSS
cd SS_CNSS2_OEMSS;git checkout SS.TOS.DM3Q;cd ..

