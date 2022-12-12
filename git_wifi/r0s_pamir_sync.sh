#!/bin/bash
#pamir-hsp
#pamir-hsp-tos



git clone https://github.qualcomm.com/SS-release-management/qcacld-3.0_R8/ qcacld-3.0
cd qcacld-3.0;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/qca-wifi-host-cmn_R8/ qca-wifi-host-cmn
cd qca-wifi-host-cmn;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/fw-api_R8/ fw-api
cd fw-api;git checkout $1;cd ..



git clone https://github.qualcomm.com/SS-release-management/Exynos_platform/ Exynos_platform
cd Exynos_platform;git checkout $1;cd ..
