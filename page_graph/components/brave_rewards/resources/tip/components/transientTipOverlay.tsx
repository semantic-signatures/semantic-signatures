/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { bindActionCreators, Dispatch } from 'redux'
import { connect } from 'react-redux'

// Components
import DonationOverlay from 'brave-ui/features/rewards/donationOverlay'

// Utils
import * as rewardsActions from '../actions/tip_actions'

interface Props extends RewardsTip.ComponentProps {
  publisher: RewardsTip.Publisher
  timeout?: number
  onTweet?: () => void
}

class TransientTipOverlay extends React.Component<Props, {}> {
  componentDidMount () {
    if (this.props.timeout) {
      setTimeout(() => {
        this.onClose()
      }, this.props.timeout)
    }
  }

  get actions () {
    return this.props.actions
  }

  onClose = () => {
    this.actions.onCloseDialog()
  }

  render () {
    let domain = ''
    let monthlyDate
    const {
      currentTipAmount,
      currentTipRecurring,
      reconcileStamp
    } = this.props.rewardsDonateData

    const publisher = this.props.publisher
    const publisherKey = publisher && publisher.publisherKey

    if (!publisherKey) {
      return null
    }

    if (currentTipRecurring && reconcileStamp) {
      monthlyDate = new Date(reconcileStamp * 1000).toLocaleDateString()
    }

    if (publisher.provider && publisher.name) {
      domain = publisher.name
    } else {
      domain = publisherKey
    }

    const verified = publisher.verified
    let logo = publisher.logo

    const internalFavicon = /^https:\/\/[a-z0-9-]+\.invalid(\/)?$/
    if (internalFavicon.test(publisher.logo)) {
      logo = `chrome://favicon/size/160@2x/${publisher.logo}`
    }

    if (!verified) {
      logo = ''
    }

    return (
      <DonationOverlay
        onClose={this.onClose}
        onTweet={!monthlyDate ? this.props.onTweet : undefined}
        success={true}
        domain={domain}
        amount={currentTipAmount}
        monthlyDate={monthlyDate}
        logo={logo}
      />
    )
  }
}

export const mapStateToProps = (state: RewardsTip.ApplicationState) => ({
  rewardsDonateData: state.rewardsDonateData
})

export const mapDispatchToProps = (dispatch: Dispatch) => ({
  actions: bindActionCreators(rewardsActions, dispatch)
})

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(TransientTipOverlay)
