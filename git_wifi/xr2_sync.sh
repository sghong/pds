#!/bin/bash
#SS.SOS.Rel.Palima.Q4

git clone https://github.qualcomm.com/SS-release-management/qcacld-3.0_S_OS/ qcacld-3.0
#cd qcacld-3.0;git checkout SS.SOS.Rel.Palima.Q4;cd ..
cd qcacld-3.0;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/qca-wifi-host-cmn_S_OS/ qca-wifi-host-cmn
#cd qca-wifi-host-cmn;git checkout SS.SOS.Rel.Palima.Q4;cd ..
cd qca-wifi-host-cmn;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/fw-api_S_OS/ fw-api
#cd fw-api;git checkout SS.SOS.Rel.Palima.Q4;cd ..
cd fw-api;git checkout $1;cd ..



#git clone https://github.qualcomm.com/SS-release-management/SS_CNSS2_OEMSS/ SS_CNSS2_OEMSS
#cd SS_CNSS2_OEMSS;git checkout SS.SOS.Rel.msm-5.10.Q4;cd ..
#cd SS_CNSS2_OEMSS;git checkout $1;cd ..

#git clone https://github.qualcomm.com/SS-release-management/INI_SS.git INI_SS

