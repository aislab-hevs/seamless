/*
 * bid.h
 *
 *  Created on: 14 gen 2018
 *      Author: peppe
 */

#ifndef HEADERS_AG_BID_H_
#define HEADERS_AG_BID_H_

class Bid {
    private:
        int contractor;
        double offer;
        double utilization;

    public:
        Bid(int contractor, double offer, double utilization = -1);
        Bid(int contractor);

        int getContractor();
        double getOffer();
        double getUtilization();
        bool equals(int contractor);

        ~Bid();
};

#endif /* HEADERS_AG_BID_H_ */
