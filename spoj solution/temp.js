import React from 'react';
import { connect } from 'react-redux';
import { Link, browserHistory } from 'react-router';
import classNames from 'classnames';

import { URLManager } from 'sprint/urls';

import { SprintComponent } from 'sprint/core/components/Component';
import { PrimaryButtonLarge } from 'sprint/core/components/Button';
import { SprintLink } from 'sprint/core/components/Link';
import { Alert } from 'sprint/core/components/Alert';
import { TeamAvatar } from 'sprint/core/components/Avatar';
import { Loading } from 'sprint/core/components/Loading';

import { SprintIdeaMainApp, IdeaView } from 'sprint/components/idea/components/IdeaApp';
import { SprintTeamMainApp, TeamHandleEdit } from 'sprint/components/team/components/TeamApp';
import { SprintTeamListingApp } from 'sprint/components/team/components/TeamListing';
import { SprintTeamConfirmationApp } from 'sprint/components/team-confirmation/components/TeamConfirmationApp';
import {
  SprintSubmissionApp,
  SprintSubmissionMandatoryChecks,
} from 'sprint/components/submission/components/SubmissionApp';

import {
  IdeaListingType,
  SubmissionListingType,
  PageSegment,
  TeamPagelet,
  TeamConfirmationType,
  OwnerIntent,
  TeamRole,
  PageletState,
  NotificationState,
} from 'sprint/constants';

import { fetchIdeas, postIdea } from 'sprint/components/idea/action';
import {
  fetchTeamInfo,
  fetchTeams,
  fetchAllUsers,
  fetchUsersToInvite,
  inviteMember,
  saveTeamDetail,
  joinTeamRequest,
  removeTeamMemberRequest,
  showRemoveBox,
  hideRemoveBox,
} from 'sprint/components/team/action';
import { fetchTeamConfirmations, updateTC } from 'sprint/components/team-confirmation/action';

import {
  fetchSubmission,
  postSubmission,
  uploadImage,
  submissionFieldSettings,
  updateSourecVisibility,
} from 'sprint/components/submission/action';

import { clearNotification } from 'sprint/core/action';

import styles from './sprint.styl';

// constant strings
const SUD = window.SUD;

class SubmissionPageSegment extends SprintComponent {
  render() {
    if (this.props.page_segment != PageSegment.SUBMISSION) return null;
    const { sprint_slug, page_segment, pagelet, submissions_info, pagelet_id } = this.props;
    let hide_submission = this.props.owner.intent == OwnerIntent.USER ? true : false;

    if (hide_submission) {
      return (
        <div className={classNames(styles.col6, styles.center_pane, 'regular')}>
          <h4 className="larger dark weight-400 less-margin-bottom">{SUD.SUBMISSION.HEADING}</h4>
          <div className={styles.warning}>
            <i className="fa fa-warning"></i>
            {SUD.SUBMISSION.BUILD_TEAM_HINT}
          </div>
          <SprintLink
            to={URLManager.getEUDTeamListingRootUrl(sprint_slug)}
            className={classNames('medium-margin', 'inline-block')}
            text={SUD.TEAM.VIEW_INVITES_REQUEST}
          />
        </div>
      );
    }

    console.log("SubmissionPageSegment", sprint_slug, page_segment, pagelet, pagelet_id);

    return (
      <SprintSubmissionApp
        event={this.props.event}
        sprint_slug={sprint_slug}
        pagelet={pagelet}
        submissions_info={submissions_info}
        postSubmission={this.props.postSubmission}
        fetchSubmission={this.props.fetchSubmission}
        fetchTeamInfo={this.props.fetchTeamInfo}
        submissionFieldSettings={this.props.submissionFieldSettings}
        uploadImage={this.props.uploadImage}
        temp_images_paths={this.props.temp_images_paths}
        owner={this.props.owner}
        submission_slug_id_map={this.props.submission_slug_id_map}
        users_info={this.props.users_info}
        submitted_submissions_ids={this.props.submitted_submissions_ids}
        draft_submissions_ids={this.props.draft_submissions_ids}
        submission_settings={this.props.submission_settings}
        user_loading_state={this.props.user_loading_state}
        updateSourecVisibility={this.props.updateSourecVisibility}
        submission_errors={this.props.errors_data.submission}
      />
    );
  }
}

class IdeaPageSegment extends SprintComponent {
  constructor(props) {
    super(props);
    this.state = {
      is_loading: false,
    };
  }

  componentWillMount() {
    // if(!this.props.owner.team_info.users.length) {
    //     this.setState({
    //         is_loading: true
    //     });
    // }
  }

  componentWillReceiveProps(nextProps) {
    if (this.props.owner.team_info.users.length != nextProps.owner.team_info.users.length) {
      this.setState({
        is_loading: false,
      });
    }
  }

  render() {
    const { sprint_slug, page_segment, pagelet, pagelet_id } = this.props;
    
    let idea_id = this.props.idea_slug_id_map[this.props.pagelet_id];
    let idea_info = this.props.ideas_info[idea_id];
    const can_edit = !(
      (this.props.event.is_idea_project_submission_format && this.props.event.idea_sub_finished) ||
      this.props.event.event_finished
    );

    const is_team_locked = this.props.owner.team_info ? this.props.owner.team_info.is_team_locked : true;

    let hide_min_team_warning = this.props.owner.team_info
      ? this.props.owner.team_info.users.length >= this.props.event.min_team_size
      : true;

    if (this.props.event.idea_sub_finished && this.props.page_segment == PageSegment.IDEA && this.props.pagelet_state === PageletState.EDIT) {
      browserHistory.push(
        URLManager.getEUDPageletStateUrl(sprint_slug, page_segment, pagelet, this.props.pagelet_id, PageletState.VIEW),
      );
    }

    console.log("IdeaPageSegment", page_segment, pagelet, pagelet_id);

    if (
      this.props.page_segment == PageSegment.IDEA &&
      (this.props.pagelet == IdeaListingType.NEW ||
        this.props.pagelet == IdeaListingType.SAMPLE ||
        this.props.pagelet_id != null)
    ) {
      if (this.props.pagelet == IdeaListingType.SAMPLE) {
        idea_info = this.props.ideas_info.sample_id;
      }
      return (
        <IdeaView
          event={this.props.event}
          sprint_slug={sprint_slug}
          page_segment={page_segment}
          pagelet={pagelet}
          pagelet_id={pagelet_id}
          idea_info={idea_info}
          postIdea={this.props.postIdea}
          owner={this.props.owner}
          fetchIdeas={this.props.fetchIdeas}
          fetchTeamInfo={this.props.fetchTeamInfo}
          pagelet_state={this.props.pagelet_state}
          user_loading_state={this.props.user_loading_state}
          idea_slug_id_map={this.props.idea_slug_id_map}
          idea_errors={this.props.errors_data.idea}
          can_edit={can_edit}
          hide_min_team_warning={hide_min_team_warning}
          submitted_ideas_ids={this.props.submitted_ideas_ids}
        />
      );
    }

    if (this.props.page_segment != PageSegment.IDEA || this.props.pagelet == IdeaListingType.NEW) return null;

    return (
      <div className={classNames(styles.flex_column)}>
        <div className={classNames(styles.col6, styles.center_pane)}>
          <SprintIdeaMainApp
            event={this.props.event}
            can_edit={can_edit}
            sprint_slug={sprint_slug}
            page_segment={page_segment}
            pagelet={pagelet}
            submitted_ideas_ids={this.props.submitted_ideas_ids}
            draft_ideas_ids={this.props.draft_ideas_ids}
            ideas_info={this.props.ideas_info}
            users_info={this.props.users_info}
            fetchIdeas={this.props.fetchIdeas}
            idea_slug_id_map={this.props.idea_slug_id_map}
            idea_errors={this.props.errors_data.idea}
            owner={this.props.owner}
          />
        </div>
        {can_edit ? (
          <div
            className={classNames(styles.col3, styles.right_pane, 'medium-margin', {
              [styles.idea_right_pane]: hide_min_team_warning,
            })}>
            {!hide_min_team_warning ? (
              <div className={classNames(styles.warning, 'regular', 'medium-margin-bottom')}>
                <i className="fa fa-warning"></i>
                {SUD.TEAM.MIN_TEAM_SIZE_WARNING} {this.props.event.min_team_size} {SUD.TEAM.MEMBERS}. <br />
                {this.props.owner.team_role == TeamRole.LEADER && this.props.owner.intent == OwnerIntent.TEAM ? (
                  <Link
                    to={URLManager.getEUDTeamPageletUrl(sprint_slug, TeamPagelet.INVITE)}
                    className="regular medium-margin yes-underline inline-block">
                    {SUD.TEAM.INVITE_MEMBERS}
                  </Link>
                ) : null}
              </div>
            ) : null}
            <SprintLink
              to={URLManager.getEUDIdeaListingUrl(sprint_slug, IdeaListingType.NEW)}
              text={SUD.IDEA.ADD_NEW}
              className="button btn-blue body-font btn-larger inline-block"></SprintLink>
            {this.props.visible_tabs.indexOf(PageSegment.TEAM_LISTING) > -1 && !is_team_locked ? (
              <div className="medium-margin">
                <div className="small light">
                  {SUD.IDEA.JOIN_TEAM_HINT}{' '}
                  <SprintLink
                    to={URLManager.getEUDTeamListingRootUrl(sprint_slug)}
                    text={SUD.IDEA.JOIN_TEAM}
                    className="small inline-block"
                  />
                </div>
              </div>
            ) : null}
          </div>
        ) : null}
        {this.props.event.idea_sub_finished && !this.props.submitted_ideas_ids.length ? (
          <div className={classNames(styles.col3, styles.right_pane, styles.idea_right_pane, 'less-margin-2')}>
            <div className={classNames('dark', 'regular', styles.warning)}>
              <i className="fa fa-warning"></i> {SUD.IDEA.IDEA_OVER}
            </div>
          </div>
        ) : null}

        <div className={styles.clearfix}></div>
      </div>
    );
  }
}

class TeamManagementSegment extends SprintComponent {
  constructor(props) {
    super(props);
    this.updateTeammatesFlag = this._updateTeammatesFlag.bind(this);
    this.state = {
      teammates: false,
    };
  }

  componentWillReceiveProps(nextProps) {
    const current_team_info = nextProps.owner.team_info;
    let is_loading = !nextProps.owner.team_info.users.length ? true : false;
    if (current_team_info) {
      this.setState({
        teammates: current_team_info.teammates,
        is_loading,
      });
    }
  }

  _updateTeammatesFlag(e) {
    const teammates_flag = e.target.checked;
    const current_team_info = this.props.owner.team_info;
    const data = {
      synopsis: current_team_info.synopsis,
      teammates: teammates_flag,
      handle: current_team_info.handle,
      attribute: 'teammate',
    };

    this.props.saveTeamDetail(data, this.props.sprint_slug);
  }

  render() {
    const { sprint_slug, page_segment, pagelet } = this.props;
    if (this.props.page_segment != PageSegment.TEAM) return null;

    const current_team_info = this.props.owner.team_info || { teammates: false, users: [] };
    let teammates_flag = this.state.teammates;
    let hide_create_team = this.props.owner.intent == OwnerIntent.USER ? true : false;
    let hide_min_team_warning = current_team_info.id
      ? current_team_info.users.length >= this.props.event.min_team_size
      : true;
    const can_edit = !(
      (this.props.event.is_idea_project_submission_format && this.props.event.idea_sub_finished) ||
      this.props.event.event_finished
    );
    const min_team_size_warning = this.props.event.is_idea_project_submission_format
      ? `${SUD.TEAM.MIN_TEAM_SIZE_WARNING}`
      : `${SUD.TEAM.MIN_TEAM_SIZE_SUBMISSION_WARNING}`;

    return (
      <div className={styles.flex_column}>
        {hide_create_team ? (
          <div className={classNames(styles.col6, styles.center_pane, 'regular')}>
            <div className="larger dark  standard-margin ">{SUD.TEAM.BUILD_TEAM}</div>
            <div className={styles.warning}>
              <i className="fa fa-warning"></i>
              {SUD.TEAM.BUILD_TEAM_HINT}
            </div>
            <SprintLink
              to={URLManager.getEUDTeamListingRootUrl(sprint_slug)}
              className={classNames('medium-margin', 'inline-block')}
              text={SUD.TEAM.VIEW_INVITES_REQUEST}
            />
          </div>
        ) : (
          <div>
            <div className={classNames(styles.col6, styles.center_pane)}>
              <SprintTeamMainApp
                can_edit={can_edit}
                event={this.props.event}
                sprint_slug={sprint_slug}
                page_segment={page_segment}
                pagelet={pagelet}
                users_info={this.props.users_info}
                users_to_invite={this.props.users_to_invite}
                teams_info={this.props.teams_info}
                owner={this.props.owner}
                inviteMember={this.props.inviteMember}
                saveTeamDetail={this.props.saveTeamDetail}
                team_confirmations={this.props.team_confirmations}
                fetchAllUsers={this.props.fetchAllUsers}
                fetchUsersToInvite={this.props.fetchUsersToInvite}
                fetchTeams={this.props.fetchTeams}
                fetchTeamInfo={this.props.fetchTeamInfo}
                removeTeamMemberRequest={this.props.removeTeamMemberRequest}
                user_loading_state={this.props.user_loading_state}
                showRemoveBox={this.props.showRemoveBox}
                hideRemoveBox={this.props.hideRemoveBox}
                user_loading_state={this.props.user_loading_state}
                field_errors={this.props.field_errors}
                invite_email={this.props.invite_email}
                notification={this.props.notification}
              />
            </div>
            {can_edit ? (
              <div
                className={classNames(
                  styles.col3,
                  styles.right_pane,
                  { [styles.idea_right_pane]: hide_min_team_warning },
                  'medium-margin',
                )}>
                <div>
                  {!hide_min_team_warning ? (
                    <div className={classNames(styles.warning, 'regular')}>
                      {min_team_size_warning} {this.props.event.min_team_size} {SUD.TEAM.MEMBERS}. <br />
                      {this.props.owner.team_role == TeamRole.LEADER ? (
                        <Link
                          to={URLManager.getEUDTeamPageletUrl(sprint_slug, TeamPagelet.INVITE)}
                          className="regular medium-margin yes-underline inline-block">
                          {SUD.TEAM.INVITE_MEMBERS}
                        </Link>
                      ) : null}
                    </div>
                  ) : null}
                  {this.props.owner.team_role == TeamRole.LEADER &&
                  this.props.event.team_size != this.props.owner.team_info.users.length ? (
                    <div>
                      <div className="regular dark">
                        <div className="inline-block v-align-middle medium-margin-right less-margin-2">
                          {SUD.TEAM.LOOKING_TEAMMATES}
                        </div>
                        <div
                          className={classNames(styles.onoffswitch, styles.yes_no, 'inline-block', 'v-align-middle')}>
                          <input
                            className={classNames(styles.onoffswitch_checkbox)}
                            value={teammates_flag}
                            checked={teammates_flag}
                            type="checkbox"
                            id="teammates_switch"
                            name="teammates_switch"
                            onChange={this._updateTeammatesFlag.bind(this)}
                          />
                          <label className={classNames(styles.onoffswitch_label)} htmlFor="teammates_switch">
                            <span
                              className={classNames(styles.onoffswitch_text)}
                              aria-label-before={SUD.SWITCH.YES}
                              aria-label-after={SUD.SWITCH.NO}></span>
                            <span className={classNames(styles.onoffswitch_switch)}></span>
                          </label>
                        </div>
                        <div className="less-margin medium-margin-bottom small light">
                          {SUD.TEAM.LOOKING_TEAMMATES_HINT}
                        </div>
                      </div>
                    </div>
                  ) : null}
                </div>

                {this.props.owner.team_role == TeamRole.LEADER ? (
                  <div>
                    <hr className="hr" />
                    <SprintTeamConfirmationApp
                      teams_info={this.props.teams_info}
                      team_confirmations_filtered={this.props.team_confirmations_filtered}
                      team_confirmations_info={this.props.team_confirmations_info}
                      users_info={this.props.users_info}
                      fetchAllUsers={this.props.fetchAllUsers}
                      fetchTeams={this.props.fetchTeams}
                      fetchTeamConfirmations={this.props.fetchTeamConfirmations}
                      tc_filter_type={TeamConfirmationType.INVITE}
                      updateTC={this.props.updateTC}
                      sprint_slug={this.props.sprint_slug}
                      user_loading_state={this.props.user_loading_state}
                    />
                  </div>
                ) : null}
              </div>
            ) : null}

            <div className={styles.clearfix}></div>
          </div>
        )}
      </div>
    );
  }
}

class AllTeamsListingSegment extends SprintComponent {
  render() {
    const { sprint_slug, page_segment } = this.props;
    if (this.props.page_segment != PageSegment.TEAM_LISTING) return null;
    let hide_team_listing = this.props.owner.intent == OwnerIntent.TEAM ? true : false;

    if (this.props.owner.team_info && this.props.owner.team_info.is_team_locked) {
      browserHistory.push(URLManager.getEUDTeamPageletUrl(sprint_slug, TeamPagelet.VIEW));
    }
    //hide_team_listing = false;
    return (
      <div className={styles.flex_column}>
        {hide_team_listing ? (
          <div className={classNames(styles.col6, styles.center_pane, 'regular')}>
            <div className="larger dark  standard-margin ">{SUD.TL.JOIN_TEAM} </div>
            <div className={styles.warning}>
              <i className="fa fa-warning"></i> {SUD.TL.JOIN_TEAM_WARNING}
            </div>
            <SprintLink
              to={URLManager.getEUDTeamManagementRootUrl(sprint_slug)}
              className={classNames('medium-margin', 'inline-block')}
              text={SUD.TEAM.VIEW_INVITES_REQUEST}
            />
          </div>
        ) : (
          <div>
            <div className={classNames(styles.col6, styles.center_pane)}>
              <SprintTeamListingApp
                event={this.props.event}
                sprint_slug={sprint_slug}
                page_segment={page_segment}
                teams_info={this.props.teams_info}
                users_info={this.props.users_info}
                owner={this.props.owner}
                team_confirmations={this.props.team_confirmations}
                joinTeamRequest={this.props.joinTeamRequest}
                fetchTeams={this.props.fetchTeams}
                fetchAllUsers={this.props.fetchAllUsers}
                user_loading_state={this.props.user_loading_state}
                teams_to_join={this.props.teams_to_join}
              />
            </div>
            <div className={classNames(styles.col3, 'standard-margin')}>
              <div className={styles.warning}>
                <div className={styles.title}>
                  <i className="fa fa-warning"></i> {SUD.TL.JOIN_TEAM_WARNING_HEAD}
                </div>
                {this.props.event.is_idea_project_submission_format ? (
                  <div className={styles.subtitle}>
                    <div className={styles.text}>{SUD.TL.JOIN_TEAM_WARNING_1}</div>
                    <div className={styles.text}>{SUD.TL.JOIN_TEAM_WARNING_2} </div>
                  </div>
                ) : (
                  <div className={styles.subtitle}>
                    <div className={styles.text}>{SUD.TL.JOIN_TEAM_WARNING_0}</div>
                  </div>
                )}
              </div>
              <SprintTeamConfirmationApp
                teams_info={this.props.teams_info}
                team_confirmations_filtered={this.props.team_confirmations_filtered}
                team_confirmations_info={this.props.team_confirmations_info}
                users_info={this.props.users_info}
                fetchTeamConfirmations={this.props.fetchTeamConfirmations}
                fetchTeams={this.props.fetchTeams}
                fetchAllUsers={this.props.fetchAllUsers}
                tc_filter_type={TeamConfirmationType.REQUEST}
                updateTC={this.props.updateTC}
                sprint_slug={this.props.sprint_slug}
                user_loading_state={this.props.user_loading_state}
              />
            </div>
          </div>
        )}
      </div>
    );
  }
}

class UserDashboardPageLeftNav extends SprintComponent {
  constructor(props) {
    super(props);
    this.state = {
      current_team_info: {
        handle: '',
        teammates: false,
      },
      intent: this.props.owner.intent,
    };
  }

  componentWillReceiveProps(nextProps) {
    let current_props_team = this.props.owner.teams_info || this.state.current_team_info;
    let next_props_team = nextProps.owner.teams_info || this.state.current_team_info;
    if (current_props_team.handle != next_props_team.handle) {
      this.setState({
        current_team_info: next_props_team,
      });
    }
    if (nextProps.owner.intent != this.props.owner.intent) {
      this.setState({
        intent: nextProps.owner.intent,
      });
    }
  }

  render() {
    const { sprint_slug, page_segment, visible_tabs } = this.props;

    if (
      this.props.page_segment == PageSegment.IDEA &&
      (this.props.pagelet == IdeaListingType.NEW ||
        this.props.pagelet == IdeaListingType.SAMPLE ||
        this.props.pagelet_id != null)
    )
      return null;
    const is_team_locked = this.props.owner.team_info ? this.props.owner.team_info.is_team_locked : true;
    const team_text =
      !this.props.submitted_ideas_ids.length && visible_tabs.indexOf(PageSegment.TEAM_LISTING) > -1 && !is_team_locked
        ? `${SUD.TEAM.BUILD_TEAM}`
        : `${SUD.TEAM.HEADING}`;
    const can_edit = !(
      (this.props.event.is_idea_project_submission_format && this.props.event.idea_sub_finished) ||
      this.props.event.event_finished
    );
    return (
      <div className={classNames(styles.graybg, styles.col3, styles.left_pane)}>
        <a
          onClick={e => {
            window.location.href = URLManager.getEventUrl(this.props.sprint_slug);
          }}>
          <h5 className={classNames(styles.event_title, styles.word_break, 'standard-margin-bottom', 'no-margin')}>
            <i className="fa fa-angle-left"></i> {this.props.event.title}
          </h5>
        </a>
        {this.props.owner.team_id ? (
          <div className={styles.team_handle_div}>
            <TeamAvatar handle={this.props.owner.team_info.handle} />
            <div className={styles.team_handle}>
              {this.props.owner.team_info.handle}

              {this.props.owner.team_role == TeamRole.LEADER && can_edit ? (
                <a className="inline-block less-margin-left no-decoration" onClick={this.props.showTeamHandleEdit}>
                  <i className="fa fa-pencil"></i>
                </a>
              ) : null}
            </div>
          </div>
        ) : null}

        {visible_tabs.indexOf(PageSegment.SUBMISSION) > -1 ? (
          <SprintLink
            to={URLManager.getEUDSubmissionRootUrl(sprint_slug)}
            className={classNames(styles.menu_item, { [styles.menu_active]: page_segment == PageSegment.SUBMISSION })}
            text={SUD.SUBMISSION.HEADING}
          />
        ) : null}

        {visible_tabs.indexOf(PageSegment.IDEA) > -1 ? (
          <SprintLink
            to={URLManager.getEUDIdeaListingRootUrl(sprint_slug)}
            className={classNames(styles.menu_item, { [styles.menu_active]: page_segment == PageSegment.IDEA })}
            text={SUD.IDEA.IDEA}
          />
        ) : null}

        {visible_tabs.indexOf(PageSegment.TEAM) > -1 ? (
          <SprintLink
            to={URLManager.getEUDTeamManagementRootUrl(sprint_slug)}
            className={classNames(
              styles.menu_item,
              { [styles.menu_active]: page_segment == PageSegment.TEAM },
              { inactive_tab: this.state.intent == OwnerIntent.USER },
            )}
            text={team_text}
          />
        ) : null}

        {!this.props.submitted_ideas_ids.length &&
        visible_tabs.indexOf(PageSegment.TEAM_LISTING) > -1 &&
        !is_team_locked ? (
          <SprintLink
            to={URLManager.getEUDTeamListingRootUrl(sprint_slug)}
            className={classNames(
              styles.menu_item,
              { [styles.menu_active]: page_segment == PageSegment.TEAM_LISTING },
              { inactive_tab: this.state.intent == OwnerIntent.TEAM },
            )}
            text={SUD.TL.JOIN_TEAM}
          />
        ) : null}
      </div>
    );
  }
}

class UserDashboardPageView extends SprintComponent {
  constructor(props) {
    super(props);
    this.showTeamHandleEdit = this._showTeamHandleEdit.bind(this);
    this.cancelUpdateTeamHandle = this._cancelUpdateTeamHandle.bind(this);
    this.saveTeamHandle = this._saveTeamHandle.bind(this);
    this.state = {
      showTeamHandleEdit: false,
      team_handle: '',
      is_loading: false,
    };
  }

  componentWillMount() {
    this.props.fetchTeamInfo();
    console.log("componentWillMount", this.props.owner.team_info);
    if (!this.props.owner.team_info.users.length) {
      this.setState({
        is_loading: true,
      });
    }
  }

  componentDidMount() {
    console.log("componentDidMount", this.props.owner.team_info);
    const current_team_info = this.props.owner.team_info || { handle: '' };
    if (current_team_info.handle) {
      this.setState({
        team_handle: current_team_info.team_handle,
      });
    }
  }

  componentWillReceiveProps(nextProps) {
    const current_team_info = nextProps.owner.team_info || { handle: '' };
    let is_loading = !nextProps.owner.team_info.users.length ? true : false;
    let showTeamHandleEdit = this.state.showTeamHandleEdit;
    if (nextProps.notification.state == NotificationState.SUCCESS) {
      showTeamHandleEdit = false;
    }
    console.log(nextProps);
    console.log("componentWillReceiveProps", this.props.owner.team_info.users.length);
    if (current_team_info.handle) {
      this.setState({
        team_handle: current_team_info.handle,
        showTeamHandleEdit: showTeamHandleEdit,
        is_loading,
      });
    }
  }

  _showTeamHandleEdit() {
    this.setState({
      showTeamHandleEdit: true,
    });
  }

  _cancelUpdateTeamHandle() {
    this.setState({
      showTeamHandleEdit: false,
    });
  }

  _saveTeamHandle(handle) {
    const current_team_info = this.props.owner.team_info;

    const data = {
      synopsis: current_team_info.synopsis,
      teammates: current_team_info.teammates,
      handle: handle,
      attribute: 'handle',
    };

    this.props.saveTeamDetail(data, this.props.sprint_slug);
  }

  render() {
    let { sprint_slug, page_segment } = this.props;
    if (this.props.event.team_size == 1 && page_segment == PageSegment.TEAM) {
      if (this.props.event.is_idea_project_submission_format) {
        browserHistory.push(URLManager.getEUDIdeaListingRootUrl(sprint_slug));
      } else {
        browserHistory.push(URLManager.getEUDSubmissionRootUrl(sprint_slug));
      }
    }

    console.log("UserDashboardPageView", this.props);

    return (
      <div className={classNames(styles.sprint_page)}>
        <Alert notification={this.props.notification} clearNotification={this.props.clearNotification} />
        <div className={styles.flex_box}>
          <UserDashboardPageLeftNav
            sprint_slug={sprint_slug}
            submitted_ideas_ids={this.props.submitted_ideas_ids}
            page_segment={page_segment}
            pagelet={this.props.pagelet}
            pagelet_id={this.props.pagelet_id}
            teams_info={this.props.teams_info}
            owner={this.props.owner}
            event={this.props.event}
            visible_tabs={this.props.visible_tabs}
            showTeamHandleEdit={this.showTeamHandleEdit}
          />

          {console.log("UserDashboardPageView Nav executed", this.props, this.state.is_loading)}

          {this.state.is_loading ? (
            <div className={classNames(styles.flex_column, styles.right_pane)}>
              <div className={classNames(styles.col6, styles.center_pane)}>
                <Loading />
              </div>
            </div>
          ) : (
            <div className={classNames(styles.flex_column, styles.right_pane)}>
              <SubmissionPageSegment {...this.props} />
              <IdeaPageSegment {...this.props} />
              <TeamManagementSegment {...this.props} />
              <AllTeamsListingSegment {...this.props} />
            </div>
          )}

          <div className={styles.clearfix}></div>
        </div>
        <TeamHandleEdit
          showTeamHandleEdit={this.state.showTeamHandleEdit}
          team_handle={this.state.team_handle}
          cancelUpdateTeamHandle={this.cancelUpdateTeamHandle}
          saveTeamHandle={this.saveTeamHandle}
        />
      </div>
    );
  }
}

const mapDispatchToProps = dispatch => {
  const props = {
    fetchIdeas: data => {
      dispatch(fetchIdeas(data));
    },
    postIdea: (data, sprint_slug, idea_listing_type, id) => {
      dispatch(postIdea(data, sprint_slug, idea_listing_type, id));
    },
    fetchAllUsers: () => {
      dispatch(fetchAllUsers());
    },
    fetchUsersToInvite: data => {
      dispatch(fetchUsersToInvite(data));
    },
    fetchTeams: data => {
      dispatch(fetchTeams(data));
    },
    fetchTeamInfo: () => {
      dispatch(fetchTeamInfo());
    },
    inviteMember: data => {
      dispatch(inviteMember(data));
    },
    saveTeamDetail: (data, sprint_slug) => {
      dispatch(saveTeamDetail(data, sprint_slug));
    },
    joinTeamRequest: data => {
      dispatch(joinTeamRequest(data));
    },
    fetchTeamConfirmations: () => {
      dispatch(fetchTeamConfirmations());
    },
    fetchSubmission: team_id => {
      dispatch(fetchSubmission(team_id));
    },
    postSubmission: (data, submission_id, sprint_slug) => {
      dispatch(postSubmission(data, submission_id, sprint_slug));
    },
    uploadImage: data => {
      dispatch(uploadImage(data));
    },
    updateTC: (data, sprint_slug, tc_filter_type) => {
      dispatch(updateTC(data, sprint_slug, tc_filter_type));
    },
    submissionFieldSettings: () => {
      dispatch(submissionFieldSettings());
    },
    removeTeamMemberRequest: (data, sprint_slug) => {
      dispatch(removeTeamMemberRequest(data, sprint_slug));
    },
    showRemoveBox: (data, action) => {
      dispatch(showRemoveBox(data, action));
    },

    hideRemoveBox: (data, action) => {
      dispatch(hideRemoveBox(data, action));
    },

    clearNotification: () => {
      dispatch(clearNotification());
    },

    updateSourecVisibility: data => {
      dispatch(updateSourecVisibility(data));
    },
  };
  return props;
};

const mapStateToProps = (state, ownProps) => {
  console.log("mapStateToProps");
  const props = {
    event: state.event,
    visible_tabs: state.visible_tabs,
    submitted_ideas_ids: state.ideas[IdeaListingType.SUBMITTED],
    draft_ideas_ids: state.ideas[IdeaListingType.DRAFT],
    users_info: state.data.users_info,
    ideas_info: state.data.ideas_info,
    teams_info: state.data.teams_info,
    owner: state.owner,
    users_to_invite: state.users_to_invite,
    team_confirmations_info: state.data.team_confirmations_info,
    team_confirmations: state.team_confirmations,
    submissions_info: state.data.submissions_info,
    submission_settings: state.submission_settings,
    temp_images_paths: state.temp_images_paths,
    team_confirmations_filtered: state.team_confirmations_filtered,
    user_loading_state: state.user_loading_state,
    notification: state.notification,
    field_errors: state.field_errors,
    idea_slug_id_map: state.idea_slug_id_map,
    errors_data: state.errors_data,
    invite_email: state.invite_email,
    teams_to_join: state.teams_to_join,
    submitted_submissions_ids: state.submissions[SubmissionListingType.SUBMITTED],
    draft_submissions_ids: state.submissions[SubmissionListingType.DRAFT],
    submission_slug_id_map: state.submission_slug_id_map,
  };

  return props;
};

const UserDashboardPage = connect(mapStateToProps, mapDispatchToProps)(UserDashboardPageView);

export class UserDashboardPageRouterAdapter extends SprintComponent {
  render() {
    const sprint_slug = this.props.params.sprint_slug;
    // change pagesegment based on phase of hackathon
    const page_segment = this.props.params.page_segment || PageSegment.TEAM;

    const pagelet = this.props.params.pagelet;

    const pagelet_id = this.props.params.pagelet_id;

    const pagelet_state = this.props.params.pagelet_state;

    return (
      <UserDashboardPage
        sprint_slug={sprint_slug}
        page_segment={page_segment}
        pagelet={pagelet}
        pagelet_id={pagelet_id}
        pagelet_state={pagelet_state}
      />
    );
  }
}



























































import React from 'react';
import ImageGallery from 'react-image-gallery';
import classNames from 'classnames';
import ReactTags from 'react-tag-autocomplete';
import 'react-tag-autocomplete/example/styles.css';
import moment from 'moment-timezone';
import Moment from 'react-moment';

import axios from 'axios';

import { SprintComponent } from 'sprint/core/components/Component';
import { SprintLink } from 'sprint/core/components/Link';
import { Link } from 'react-router';
import { PrimaryButton } from 'sprint/core/components/Button';
import { Loading } from 'sprint/core/components/Loading';

import { URLManager, ApiURLManager } from 'sprint/urls';
import { SubmissionPagelet, CSRFHeader, 
  TeamRole, TeamPagelet, SubmissionListingType, PageSegment,
  PageletState
} from 'sprint/constants';

import styles from 'sprint/page/UserDashboard/sprint.styl';
import submission_styles from './submission.styl';

import 'react-image-gallery/styles/css/image-gallery.css';

// constant strings
const SUD = window.SUD;
Moment.globalFormat = 'lll z';

export class SprintSubmissionApp extends SprintComponent {
  constructor(props) {
    super(props);
    this.state = {
      is_loading: false,
    };
  }

  componentWillMount() {
    this.props.submissionFieldSettings();
    this.props.fetchSubmission(this.props.owner.team_id);
    if (this.props.owner.team_info.users.length < 1) {
      this.setState({
        is_loading: true,
      });
    }
  }

  componentWillReceiveProps(nextProps) {
    if (nextProps.owner.team_info.users.length > 0) {
      this.setState({
        is_loading: false,
      });
    }
  }

  formatDateTime(datetime_str, timezone) {
    if (!datetime_str) {
      return null;
    }
    let date = moment(datetime_str, moment.ISO_8601);
    if (timezone) {
      date = date.tz(timezone).format('MMM D, YYYY [at] h:mm A z');
    } else {
      date = date.format('MMM D, YYYY [at] h:mm A z');
    }
    return date;
  }

  render() {
    let { sprint_slug, pagelet } = this.props;
    console.log("SprintSubmissionApp", this.props, sprint_slug, pagelet);

    if (this.props.submitted_submissions_ids.length) {
      pagelet = pagelet || SubmissionListingType.SUBMITTED;
    } else {
      pagelet = pagelet || SubmissionListingType.DRAFT;
    }

    const timezone = this.props.owner.timezone || this.props.event.timezone;
    const extra_props = {
      ...this.props,
      pagelet,
      timezone: timezone,
      formatDateTime: this.formatDateTime,
    };

    if (this.state.is_loading) {
      return (
        <div className={classNames(styles.col6, styles.center_pane)}>
          <Loading />
        </div>
      );
    }

    // not shortlisted
    if (
      this.props.event.is_idea_project_submission_format &&
      this.props.event.idea_sub_finished &&
      this.props.event.event_started &&
      !this.props.submission_settings.shortlisted_ideas.length
    ) {
      return (
        <div className={classNames(styles.col6, styles.center_pane)}>
          <h4 className="larger dark weight-400 less-margin-2-bottom">{SUD.SUBMISSION.HEADING}</h4>
          <div className={classNames(styles.warning, 'regular')}>
            <i className="fa fa-warning"></i> {SUD.SUBMISSION.NOT_SHORTLISTED}
          </div>
        </div>
      );
    }

    // minimum team not met
    if (this.props.event.event_started && this.props.owner.team_info.users.length < this.props.event.min_team_size) {
      return (
        <div className={classNames(styles.col6, styles.center_pane)}>
          <h4 className="larger dark weight-400 less-margin-2-bottom">{SUD.SUBMISSION.HEADING}</h4>
          <div className={classNames(styles.warning, 'regular', 'inline-block')}>
            <i className="fa fa-warning"></i>
            <span>
              {SUD.TEAM.MIN_TEAM_SIZE_SUBMISSION_WARNING} {this.props.event.min_team_size} {SUD.TEAM.MEMBERS}. <br />
            </span>
            {this.props.owner.team_role == TeamRole.LEADER ? (
              <a
                href={URLManager.getEUDTeamPageletUrl(sprint_slug, TeamPagelet.INVITE)}
                className="regular less-margin-2 inline-block yes-underline">
                {SUD.TEAM.INVITE_MEMBERS}
              </a>
            ) : null}
          </div>
        </div>
      );
    }

    const submitted_text = this.props.submitted_submissions_ids.length
      ? `${SUD.SUBMISSION.SUBMITTED} [` + this.props.submitted_submissions_ids.length + ']'
      : `${SUD.SUBMISSION.SUBMITTED}`;
    const draft_text = this.props.draft_submissions_ids.length
      ? `${SUD.SUBMISSION.DRAFTS} [` + this.props.draft_submissions_ids.length + ']'
      : `${SUD.SUBMISSION.DRAFTS}`;

    // other cases
    return (
      <div className={classNames(styles.col6, styles.center_pane)}>
        <div className="larger dark  standard-margin standard-margin-bottom ">{SUD.SUBMISSION.HEADING}</div>

        {this.props.event.event_started ? (
          <div>
            <div className={styles.listing_navbar}>
              {this.props.submitted_submissions_ids.length ? (
                <SprintLink
                  to={URLManager.getEUDSubmissionListingUrl(sprint_slug, SubmissionListingType.SUBMITTED)}
                  className={classNames(styles.listing_navbar_item, {
                    [styles.active]: pagelet == SubmissionListingType.SUBMITTED,
                  })}
                  text={submitted_text}
                />
              ) : null}

              {this.props.draft_submissions_ids.length ? (
                <SprintLink
                  to={URLManager.getEUDSubmissionListingUrl(sprint_slug, SubmissionListingType.DRAFT)}
                  className={classNames(styles.listing_navbar_item, { [styles.active]: pagelet == SubmissionListingType.DRAFT })}
                  text={draft_text}
                />
              ) : null}
            </div>
            {/* <SubmissionBodyView {...extra_props} />
            <SubmissionEdit {...extra_props} /> */}
            {console.log("I am here in sprintsubmission app")}
            <SubmittedSubmissionListing {...extra_props} />
            <DraftsSubmissionListing {...extra_props} />
            {/* <SubmissionBodyView {...extra_props} /> */}
          </div>
        ) : (
          // not started yet
          <div className={classNames(styles.center_pane, styles.col6)}>
            <h3 className="large-18 bold dark standard-margin-bottom standard-margin ">
              {SUD.SUBMISSION.EVENT_START_WARING}{' '}
              <Moment tz={timezone} locale={window.app_settings.parsed_language_code}>
                {this.props.event.start}
              </Moment>
            </h3>
          </div>
        )}
      </div>
    );
  }
}

class SprintSubmissionDetail extends SprintComponent {
  constructor(props) {
    super(props);
    this.state = {
      data: {
        title: '',
        author: '',
        last_updated: '',
        idea: {
          id: null,
          title: '',
        },
      },
    };
  }

  formatDateTime(datetime_str, timezone) {
    if (!datetime_str) {
      return null;
    }
    let date = moment(datetime_str, moment.ISO_8601);
    if (timezone) {
      date = date.tz(timezone).format('MMM D, YYYY [at] h:mm A z');
    } else {
      date = date.format('MMM D, YYYY [at] h:mm A z');
    }
    return date;
  }

  render() {
    console.log("SprintSubmissionDetail", this.props);
    const data = this.props.data || this.state.data;
    const can_edit = !this.props.event.event_finished;

    let submission_url = null;
    let submission_edit_url = null;
    if (data) {
      submission_url = URLManager.getEUDPageletIdUrl(
        this.props.sprint_slug,
        this.props.page_segment,
        this.props.pagelet,
        data.slug,
      );
      submission_edit_url = URLManager.getEUDPageletStateUrl(
        this.props.sprint_slug,
        this.props.page_segment,
        this.props.pagelet,
        data.slug,
        PageletState.EDIT,
      );
      if (data.id == 'sample_id') {
        submission_url = URLManager.getEUDIdeaListingUrl(this.props.sprint_slug, SubmissionListingType.SAMPLE);
      }
    }

    console.log(submission_edit_url);

    const timezone = this.props.owner.timezone || this.props.event.timezone;

    return (
      <div className={classNames(styles.listing_item, styles.flex_box)}>
        <div className={styles.flex_column}>
          <Link to={submission_url} className="inline-block less-margin-2-bottom">
            <h4 className={styles.title}>{data.title}</h4>
          </Link>
          <Link to={submission_url}>
            <div className={styles.subtitle}>
              {this.props.event.is_idea_project_submission_format ? (
                <div className="inline-block">
                  {data.idea && data.idea.title ? (
                    <span> {data.idea.title} </span>
                  ) : (
                    <span>{SUD.SUBMISSION.NOT_SELECTED}</span>
                  )}
                </div>
              ) : null}
              <span>
                {SUD.SUBMISSION.AUTHOR}:&nbsp;
                {data.id == 'sample_id' ? (
                  <span>{data.author}</span>
                ) : (
                  <span>{this.props.users_info[data.author] ? this.props.users_info[data.author].full_name : ' '}</span>
                )}
              </span>
              <span>
                {SUD.SUBMISSION.ADDED_ON}:{' '}
                <Moment tz={timezone} locale={window.app_settings.parsed_language_code}>
                  {data.last_updated}
                </Moment>
              </span>
            </div>
          </Link>
        </div>

        {data.id != 'sample_id' &&
        can_edit ? (
          <div className={classNames('regular', 'align-right')}>
            <Link to={submission_edit_url}>
              <i className="fa light fa-pencil"></i>
            </Link>
          </div>
        ) : null}

        {data.id == 'sample_id' ? (
          <div className={classNames('float-right', 'small', 'align-right', styles.warning_text)}>
            {SUD.SUBMISSION.SAMPLE_SUBMISSION_TEXT}
          </div>
        ) : null}

      <div className="clear"></div>
      </div>
    );
  }
}

class DraftsSubmissionListing extends SprintComponent {
  isSubmissionDraftsListingPagelet() {
    return this.props.pagelet == SubmissionListingType.DRAFT;
  }

  render() {
    if (!this.isSubmissionDraftsListingPagelet()) return null;

    let { sprint_slug, pagelet, submissions_info } = this.props;
    console.log("DraftSubmissionListing", this.props, sprint_slug, pagelet, submissions_info);

    return (
      <div>
        <div className={styles.listing}>
          {this.props.draft_submissions_ids.map((idea_id, index) => {
            const data = this.props.submissions_info[idea_id];
            return (
              <SprintSubmissionDetail
                key={index}
                data={data}
                users_info={this.props.users_info}
                sprint_slug={this.props.sprint_slug}
                page_segment={PageSegment.SUBMISSION}
                pagelet={SubmissionListingType.DRAFT}
                event={this.props.event}
                owner={this.props.owner}
              />
            );
          })}
        </div>
      </div>
    );
  }
}

class SubmittedSubmissionListing extends SprintComponent {
  isSubmissionSubmittedListingPagelet() {
    return this.props.pagelet == SubmissionListingType.SUBMITTED;
  }

  render() {
    if (!this.isSubmissionSubmittedListingPagelet()) return null;

    let { sprint_slug, pagelet, submissions_info } = this.props;
    console.log("SubmittedSubmissionListing", this.props, sprint_slug, pagelet, submissions_info);

    return (
      <div>
        <div className={styles.listing}>
          {this.props.submitted_submissions_ids.map((idea_id, index) => {
            const data = this.props.submissions_info[idea_id];
            return (
              <SprintSubmissionDetail
                key={index}
                data={data}
                users_info={this.props.users_info}
                sprint_slug={this.props.sprint_slug}
                page_segment={PageSegment.SUBMISSION}
                pagelet={SubmissionListingType.SUBMITTED}
                event={this.props.event}
                owner={this.props.owner}
              />
            );
          })}
        </div>
      </div>
    );
  }
}

class SubmissionEdit extends SprintComponent {
  constructor(props) {
    super(props);
    this.handleUpdate = this._handleUpdate.bind(this);
    this.postSubmission = this._postSubmission.bind(this);
    this.handleTagAddition = this._handleTagAddition.bind(this);
    this.handleTagDelete = this._handleTagDelete.bind(this);
    this.deleteScreenshot = this._deleteScreenshot.bind(this);
    this.uploadFileOns3 = this._uploadFileOns3.bind(this);
    this.state = {
      submissions_info: {
        title: '',
        idea: '',
        theme: '',
        demo_link: '',
        source_url: '',
        video_url: '',
        presentation: '',
        attachment: '', //source
        custom_attachment: '',
        description_text: '', //Description of the submission in sprint
        description: '',
        instruction_text: '', //Instructions to run the submission
        instruction: '',
        special_prizes: [],
        custom_team_id: '',
        fetch_repo_from_link: false,
        tags: '',
        tags_parsed: [],
        screenshots: [],
        screenshots_ids: [],
        special_prizes: [],
        source_visibility: false,
        valid: false, // complete/incomplete submission
      },
      tags_suggestions: [],
      image_upload_state: {
        isUploading: {
          screenshots: false,
          attachment: false,
          presentation: false,
          custom_attachment: false,
        },
        percentCompleted: {
          creenshots: 0,
          attachment: 0,
          presentation: 0,
          custom_attachment: 0,
        },
      },
      currentImageIndex: null,
      submission_errors: {
        title: '',
        theme: '',
      },
      allow_publish: false,
    };
  }

  componentWillMount() {
    axios.get('/users/AJAX/skills-json/').then(response => {
      let tags = [...this.state.tags_suggestions];
      response.data.map((tag, index) => {
        const ts = { id: index, name: tag };
        tags.push(ts);
      });
      this.setState({
        tags_suggestions: tags,
      });
    });
  }

  componentWillReceiveProps(nextProps) {
    let submission_errors = { ...this.state.submission_errors };
    let has_error = false;

    for (var key in nextProps.submission_errors) {
      if (nextProps.submission_errors.hasOwnProperty(key)) {
        if (submission_errors[key] !== nextProps.submission_errors[key]) {
          submission_errors[key] = nextProps.submission_errors[key];
          has_error = true;
        }
      }
    }

    let submissions_info = { ...this.state.submissions_info };

    const submission_btn_loading =
      this.props.user_loading_state[this.props.owner.user_id] &&
      this.props.user_loading_state[this.props.owner.user_id].submission;

    if (nextProps.submissions_info.id && !has_error && !submission_btn_loading) {
      let tags_parsed = nextProps.submissions_info.tags ? nextProps.submissions_info.tags.split(',') : [];
      tags_parsed = tags_parsed.map((tag, index) => {
        return { id: index, name: tag };
      });
      const screenshots_ids = this.state.submissions_info.screenshots.map(sc => sc.id);
      submissions_info = {
        ...submissions_info,
        ...nextProps.submissions_info,
        tags_parsed,
        screenshots_ids,
        custom_team_id: nextProps.submissions_info.custom_team_id || '',
        idea: nextProps.submissions_info.idea ? nextProps.submissions_info.idea.id : '',
        theme: nextProps.submissions_info.theme ? nextProps.submissions_info.theme.id : '',
      };
    }

    let tags_suggestions = [...this.state.tags_suggestions];
    if (nextProps.submission_settings.mlh_hardwares_json && nextProps.submission_settings.mlh_hardwares_json.length) {
      nextProps.submission_settings.mlh_hardwares_json.map((tag, index) => {
        const ts = { id: index, name: tag };
        tags_suggestions.push(ts);
      });
    }

    let allow_publish = this.props.owner.team_info.is_team_locked;
    this.setState({
      submissions_info,
      submission_errors,
      allow_publish,
      tags_suggestions,
    });
  }

  _handleUpdate(attribute, e) {
    let data = e.target.value;
    if (attribute == 'presentation' || attribute == 'attachment' || attribute == 'custom_attachment') {
      data = e.target.files[0];
    }
    if (attribute == 'special_prizes') {
      if (e.target.checked) {
        data = [...this.state.submissions_info.special_prizes, parseInt(data)];
      } else {
        let index = this.state.submissions_info.special_prizes.indexOf(parseInt(data));
        if (index > -1) {
          data = [
            ...this.state.submissions_info.special_prizes.slice(0, index),
            ...this.state.submissions_info.special_prizes.slice(index + 1),
          ];
        }
      }
    }
    if (attribute == 'fetch_repo_from_link') {
      data = e.target.checked;
    }
    if (attribute == 'source_visibility') {
      data = e.target.checked;
      const state = { state: data };
      this.props.updateSourecVisibility(state);
    }
    const submissions_info = { ...this.state.submissions_info, ...{ [attribute]: data } };

    this.setState({
      submissions_info: submissions_info,
    });
  }

  _postSubmission() {
    let submissions_info = { ...this.state.submissions_info };
    let submission_errors = { ...this.state.submission_errors };
    let has_error = false;
    const mandatory_fields = [...this.props.submission_settings.mandatory_fields];
    let valid = this.state.submissions_info.valid;
    if (!mandatory_fields.length) {
      valid = true;
    } else {
      valid = mandatory_fields.reduce((valid, mf) => {
        let field = mf.split('_required')[0];
        if (this.state.submissions_info[field]) {
          valid = true;
        } else {
          valid = false;
        }
        return valid;
      }, valid);
    }
    if (!submissions_info.title) {
      submission_errors.title = `${SUD.IDEA.FIELD_ERROR}`;
      valid = false;
      has_error = true;
    } else {
      submission_errors.title = '';
    }
    if (
      !this.props.event.is_idea_project_submission_format &&
      this.props.event.themes.length &&
      !submissions_info.theme
    ) {
      submission_errors.theme = `${SUD.IDEA.FIELD_ERROR}`;
      valid = false;
      has_error = true;
    } else {
      submission_errors.theme = '';
    }

    if (this.props.event.is_idea_project_submission_format && !submissions_info.idea) {
      submission_errors.idea = `${SUD.IDEA.FIELD_ERROR}`;
      valid = false;
      has_error = true;
    } else {
      submission_errors.idea = '';
    }

    if (has_error) {
      this.setState({ submission_errors });
      window.scrollTo(0, 0);
      return null;
    }

    const tags_parsed = this.state.submissions_info.tags_parsed.map(tag => tag.name);
    const tags = `${tags_parsed.join(',')}`;
    //const special_prizes = this.state.submissions_info.special_prizes.map(sp => sp.id);

    submissions_info = {
      ...this.state.submissions_info,
      theme: parseInt(this.state.submissions_info.theme),
      idea: parseInt(this.state.submissions_info.idea),
      team_id: this.props.owner.team_id,
      tags: tags,
      screenshots: this.state.submissions_info.screenshots_ids,
      valid: valid,
      //special_prizes: special_prizes
    };

    this.props.postSubmission(submissions_info, submissions_info.id, this.props.sprint_slug);
    this.props.fetchTeamInfo();
  }

  _uploadFileOns3(attribute, e) {
    let file = e.target.files[0];
    let fileName = file.name.substring(0, file.name.lastIndexOf('.'));
    const ext = file.name.substring(file.name.lastIndexOf('.'));
    fileName = fileName.replace(/[^a-z0-9]/gi, '_').toLowerCase();
    fileName = fileName.concat(ext);

    if (file && attribute == 'screenshots') {
      let mimeType = file.type; // You can get the mime type
      if (mimeType.indexOf('image') == -1) {
        alert(`${SUD.SUBMISSION.UNSUPPORTED_EXT}`);
        return false;
      }
      if (file.size > 3 * 1024 * 1024) {
        alert(`${SUD.SUBMISSION.MAX_IMAGE_FILE_SIZE}`);
        return false;
      }
    }

    if (
      attribute == 'presentation' ||
      attribute == 'attachment' ||
      attribute == 'custom_attachment' ||
      (attribute == 'screenshots' && file)
    ) {
      if (file.size > 400 * 1024 * 1024) {
        alert(`${SUD.SUBMISSION.MAX_FILE_UPLOAD_SIZE}`);
        return false;
      }

      // get request to presignedurl
      let src = null;
      let local_src = URL.createObjectURL(file);

      axios
        .get(ApiURLManager.prefetchSignedURl(), {
          params: {
            ContentType: file.type,
            fileName: fileName,
            fileSource: attribute,
            team_id: this.props.owner.team_id,
          },
        })
        .then(response => {
          let signed_url = response.data.url;
          src = response.data.name;

          let image_upload_state = {
            isUploading: {
              ...this.state.image_upload_state.isUploading,
              [attribute]: true,
            },
            percentCompleted: {
              ...this.state.image_upload_state.percentCompleted,
              [attribute]: 0,
            },
          };
          this.setState({ image_upload_state: image_upload_state });

          let config = {
            headers: {
              'Content-Type': file.type,
              'X-CSRFToken': csrftoken,
            },
            onUploadProgress: progressEvent => {
              let percentCompleted = Math.round((progressEvent.loaded * 100) / progressEvent.total);
              let image_upload_state = {
                isUploading: {
                  ...this.state.image_upload_state.isUploading,
                  [attribute]: true,
                },
                percentCompleted: {
                  ...this.state.image_upload_state.percentCompleted,
                  [attribute]: percentCompleted,
                },
              };
              this.setState({ image_upload_state: image_upload_state });
            },
          };
          return axios.put(signed_url, file, config).then(response => {
            if (src) {
              let submissions_info = {};
              if (attribute == 'screenshots') {
                let screenshots = this.state.submissions_info.screenshots || [];
                submissions_info = { ...this.state.submissions_info };

                return axios
                  .post(ApiURLManager.createSubmissionScreenshot(), { screenshot: src }, CSRFHeader)
                  .then(response => {
                    let screenshots_ids = this.state.submissions_info.screenshots_ids || [];
                    screenshots_ids.push(response.data.id);
                    screenshots.push(response.data);
                    submissions_info = { ...submissions_info, screenshots_ids, screenshots };
                    this.setState({
                      submissions_info: submissions_info,
                    });
                  });
              } else {
                submissions_info = { ...this.state.submissions_info, ...{ [attribute]: src } };
                this.setState({
                  submissions_info: submissions_info,
                });
              }
            }
          });
        })
        .then(() => {
          let image_upload_state = {
            isUploading: {
              ...this.state.image_upload_state.isUploading,
              [attribute]: false,
            },
            percentCompleted: {
              ...this.state.image_upload_state.percentCompleted,
              [attribute]: 100,
            },
          };
          this.setState({ image_upload_state: image_upload_state });
        });
    }
  }

  _handleTagDelete(i) {
    let tags_parsed = this.state.submissions_info.tags_parsed;
    tags_parsed = [...tags_parsed.slice(0, i), ...tags_parsed.slice(i + 1)];
    const submissions_info = { ...this.state.submissions_info, tags_parsed };
    this.setState({ submissions_info });
  }

  _handleTagAddition(tag) {
    if (!tag.id) {
      const last_tag = this.state.submissions_info.tags_parsed.slice(-1)[0];
      tag.id = last_tag ? last_tag.id + 1 : 0;
    }
    const tags_parsed = [].concat(this.state.submissions_info.tags_parsed, tag);
    const submissions_info = { ...this.state.submissions_info, ...{ tags_parsed } };
    this.setState({ submissions_info });
  }

  _renderCustomControls() {
    const index = this._imageGallery ? this._imageGallery.state.currentIndex : '';
    return (
      <a
        className={classNames(submission_styles.remove_image, 'tool-tip')}
        title={SUD.SUBMISSION.DELETE_SCREENSHOT}
        onClick={this._deleteScreenshot.bind(this, index)}>
        <i className="fa fa-times-circle fa-2x fa-red"></i>
      </a>
    );
  }

  _deleteScreenshot(id) {
    const screenshots = this.state.submissions_info.screenshots;
    const screenshots_ids = this.state.submissions_info.screenshots_ids;

    const submissions_info = {
      ...this.state.submissions_info,
      screenshots: [...screenshots.slice(0, id), ...screenshots.slice(id + 1)],
      screenshots_ids: [...screenshots_ids.slice(0, id), ...screenshots_ids.slice(id + 1)],
    };

    this.setState({ submissions_info });
  }

  render() {
    if (this.props.pagelet != SubmissionPagelet.EDIT) return null;
    const { submissions_info, submission_errors, image_upload_state } = this.state;
    const event_themes = this.props.event.themes;
    const { submission_settings } = this.props;
    const ss_visible_fields = this.props.submission_settings.visible_fields || [];
    let images = [];
    const screenshots = submissions_info.screenshots || [];
    screenshots.map(img => {
      images.push({
        original: img.screenshot ? img.screenshot.split('?')[0] : img.screenshot,
        thumbnail: img.screenshot ? img.screenshot.split('?')[0] : img.screenshot,
        id: img.id,
      });
    });
    const file_fields = ['attachment', 'presentation', 'custom_attachment'];
    let file_fields_path = {};
    for (let file of file_fields) {
      if (submissions_info[file]) {
        let attachment_file_path = submissions_info[file].split('/');
        attachment_file_path = attachment_file_path[attachment_file_path.length - 1];
        file_fields_path[file] = attachment_file_path.split('?')[0];
      }
    }
    const can_edit = !this.props.event.event_finished;
    const submission_btn_loading =
      this.props.user_loading_state[this.props.owner.user_id] &&
      this.props.user_loading_state[this.props.owner.user_id].submission;

    let submission_btn_disabled = submission_btn_loading || false;

    // if(this.state.allow_publish) {
    //     submission_btn_disabled = false;
    // }

    // if(image_upload_state.isUploading.screenshots || image_upload_state.isUploading.attachment || image_upload_state.isUploading.presentation || image_upload_state.isUploading.custom_attachment) {
    //     submission_btn_disabled = true;
    // }

    const _imageGallery = null;
    const private_source_hint = !submissions_info.source_visibility ? `${SUD.SUBMISSION.PRIVATE_SOURCE_HINT}` : '';
    let source_code_hint = `${SUD.SUBMISSION.SOURCE_URL_HINT}`;
    if (this.props.event.is_listed) {
      source_code_hint = `${SUD.SUBMISSION.SOURCE_URL_HINT_LISTED}`;
    }

    // show mandatory warning
    const mandatory_fields = [...this.props.submission_settings.mandatory_fields];
    let valid = this.state.submissions_info.valid;
    let mandatory_fields_left = [];
    let left_count = 0;
    if (!mandatory_fields.length) {
      valid = true;
    } else {
      left_count = mandatory_fields.reduce((left_count, mf) => {
        let field = mf.split('_required')[0];
        if (
          !this.state.submissions_info[field] ||
          (this.state.submissions_info[field] && !this.state.submissions_info[field].length)
        ) {
          left_count++;
          let field_label = field.toUpperCase() + '_LABEL';
          if (field === 'custom_attachment') {
            mandatory_fields_left.unshift(this.props.submission_settings.custom_field_title);
          } else {
            mandatory_fields_left.unshift(`${SUD.SUBMISSION[field_label]}`);
          }
        }
        return left_count;
      }, left_count);

      valid = left_count ? false : true;
    }

    return (
      <div className={styles.flex_column}>
        <div className={classNames(styles.col6, styles.center_pane)}>
          <h4 className="larger dark weight-400 less-margin-bottom">{SUD.SUBMISSION.HEADING}</h4>

          {/* title */}

          <SubmissionFieldInput
            value={submissions_info.title}
            label={SUD.SUBMISSION.TITLE}
            attribute="title"
            handleUpdate={this.handleUpdate}
            submission_errors={submission_errors}
          />

          {/* team id */}
          {ss_visible_fields.indexOf('show_custom_team_id') > -1 ? (
            <SubmissionFieldInput
              value={submissions_info.custom_team_id}
              label={SUD.SUBMISSION.TEAM_ID}
              hint={SUD.SUBMISSION.TEAM_ID_HINT}
              attribute="custom_team_id"
              handleUpdate={this.handleUpdate}
              submission_errors={submission_errors}
            />
          ) : null}

          {/* theme */}
          {this.props.event.is_idea_project_submission_format ? (
            <div className={classNames(styles.styled_input, { [styles.error_form]: submission_errors.idea })}>
              <select
                id="id_idea"
                name="idea"
                value={submissions_info.idea}
                onChange={e => {
                  this.handleUpdate('idea', e);
                }}>
                <option value="">{SUD.SUBMISSION.IDEA_LABEL}</option>
                {submission_settings.shortlisted_ideas.map((idea, key) => (
                  <option value={idea.id} key={key}>
                    {idea.title}{' '}
                  </option>
                ))}
              </select>
              <label className={classNames('dark', 'large')}>{SUD.SUBMISSION.IDEA_LABEL}</label>
              <span className={classNames(styles.error_span)}>{SUD.IDEA.FIELD_ERROR}</span>
              <div className={classNames('light', 'small', 'less-margin-2')}>{SUD.SUBMISSION.IDEA_HINT}</div>
            </div>
          ) : (
            <div>
              {this.props.event.themes.length ? (
                <div className={classNames(styles.styled_input, { [styles.error_form]: submission_errors.theme })}>
                  <select
                    id="id_theme"
                    name="theme"
                    value={submissions_info.theme}
                    onChange={e => {
                      this.handleUpdate('theme', e);
                    }}>
                    <option value="">{SUD.IDEA.THEME_LABEL}</option>
                    {event_themes.map((theme, key) => (
                      <option value={theme.id} key={key}>
                        {theme.title}{' '}
                      </option>
                    ))}
                  </select>
                  <label className={classNames('dark', 'large')}>{SUD.SUBMISSION.IDEA_LABEL}</label>
                  <span className={classNames(styles.error_span)}>{SUD.IDEA.FIELD_ERROR}</span>
                  <div className={classNames('light', 'small', 'less-margin-2')}>{SUD.SUBMISSION.THEME_HINT}</div>
                </div>
              ) : null}
            </div>
          )}

          {/* Project Description */}
          <div className={classNames(styles.styled_input)}>
            <SubmissionFieldInput
              value={submissions_info.description_text}
              label={SUD.SUBMISSION.DESCRIPTION_TEXT_LABEL}
              hint={SUD.SUBMISSION.DESCRIPTION_HINT}
              attribute="description_text"
              handleUpdate={this.handleUpdate}
              field_type="textarea"
              submission_errors={submission_errors}
            />
          </div>

          {/* Built With */}
          <div className={classNames(styles.styled_input)}>
            <ReactTags
              tags={submissions_info.tags_parsed}
              suggestions={this.state.tags_suggestions}
              allowNew={false}
              handleDelete={this.handleTagDelete.bind(this)}
              handleAddition={this.handleTagAddition.bind(this)}
              placeholder={SUD.SUBMISSION.TAGS_LABEL}
              delimiters={[188, 32, 13, 9]}
              minQueryLength={1}
            />

            {this.props.event.is_mlh_hackathon ? (
              <div className={classNames('light', 'small', 'less-margin-2')}>{SUD.SUBMISSION.TAGS_MLH_HINT}</div>
            ) : (
              <div className={classNames('light', 'small', 'less-margin-2')}>{SUD.SUBMISSION.TAGS_HINT}</div>
            )}
          </div>

          {/* Snapshots */}
          {ss_visible_fields.indexOf('show_screenshots') > -1 ? (
            <div>
              <SubmissionFieldFile
                attribute="screenshots"
                image_upload_state={this.state.image_upload_state}
                uploadFileOns3={this.uploadFileOns3}
                label={SUD.SUBMISSION.SNAPSHOT_LABEL}
                hint={SUD.SUBMISSION.SCREENSHOTS_HINT}
                submission_errors={submission_errors}
              />

              {images.length ? (
                <div className={submission_styles.screenshots}>
                  <ImageGallery
                    ref={i => (this._imageGallery = i)}
                    showIndex={true}
                    items={images}
                    slideInterval={2000}
                    onImageLoad={this.handleImageLoad}
                    renderCustomControls={this._renderCustomControls.bind(this)}
                  />
                </div>
              ) : null}
            </div>
          ) : null}

          {/* Video Link */}
          {ss_visible_fields.indexOf('show_video_url') > -1 ? (
            <SubmissionFieldInput
              value={submissions_info.video_url}
              label={SUD.SUBMISSION.VIDEO_URL_LABEL}
              attribute="video_url"
              hint={SUD.SUBMISSION.VIDEO_HINT}
              handleUpdate={this.handleUpdate}
              submission_errors={submission_errors}
            />
          ) : null}

          {/* Presentation */}
          {ss_visible_fields.indexOf('show_presentation') > -1 ? (
            <SubmissionFieldFile
              attribute="presentation"
              image_upload_state={this.state.image_upload_state}
              uploadFileOns3={this.uploadFileOns3}
              label={SUD.SUBMISSION.PRESENTATION_LABEL}
              value={submissions_info.presentation}
              file_path={file_fields_path['presentation']}
              submission_errors={submission_errors}
            />
          ) : null}

          {/* Demo Link */}
          {ss_visible_fields.indexOf('show_demo_link') > -1 ? (
            <SubmissionFieldInput
              value={submissions_info.demo_link}
              label={SUD.SUBMISSION.DEMO_LINK_LABEL}
              attribute="demo_link"
              hint={SUD.SUBMISSION.DEMO_HINT}
              handleUpdate={this.handleUpdate}
              submission_errors={submission_errors}
            />
          ) : null}

          {/* Special Prizes */}
          {submission_settings.special_prizes.length ? (
            <div className={classNames(styles.form_wrapper)}>
              <label className={classNames('dark', 'large')}>{SUD.SUBMISSION.SPECIAL_PRIZES_LABEL}</label>
              <div className={classNames('light', 'small', 'less-margin-2', 'less-margin-2-bottom')}>
                {SUD.SUBMISSION.SPECIAL_PRIZES_HINT}
              </div>
              {submission_settings.special_prizes.map(sp => {
                return (
                  <div key={sp.id} className="custom-checkbox">
                    <input
                      type="checkbox"
                      className="v-align-middle"
                      onChange={e => {
                        this.handleUpdate('special_prizes', e);
                      }}
                      value={sp.id}
                      name="special_prizes"
                      checked={submissions_info.special_prizes.indexOf(sp.id) > -1}
                    />
                    <label>{sp.title}</label>
                  </div>
                );
              })}
            </div>
          ) : null}

          {/* Project Source */}
          {ss_visible_fields.indexOf('show_source_url') > -1 ||
          ss_visible_fields.indexOf('show_attachment') > -1 ||
          ss_visible_fields.indexOf('show_custom_attachment') > -1 ||
          ss_visible_fields.indexOf('show_instruction_text') > -1 ? (
            <div className={classNames(styles.form_wrapper)}>
              <div className={classNames('float-left')}>
                <label className={classNames('dark', 'large')}>{SUD.SUBMISSION.PROJECT_SOURCE_LABEL}</label>
                {submissions_info.id ? (
                  <div className={classNames('light', 'small', 'less-margin-2')}>
                    {SUD.SUBMISSION.PROJECT_SOURCE_HINT}
                  </div>
                ) : null}
              </div>
              {submissions_info.id ? (
                <div className={classNames('float-right')}>
                  <div className={classNames(styles.onoffswitch)}>
                    <input
                      className={classNames(styles.onoffswitch_checkbox)}
                      value={submissions_info.source_visibility}
                      checked={submissions_info.source_visibility}
                      onChange={e => {
                        this.handleUpdate('source_visibility', e);
                      }}
                      type="checkbox"
                      name="onoffswitch"
                      id="project_source_switch"
                    />
                    <label className={classNames(styles.onoffswitch_label)} htmlFor="project_source_switch">
                      <span
                        className={classNames(styles.onoffswitch_text)}
                        aria-label-before={SUD.SWITCH.SHOW}
                        aria-label-after={SUD.SWITCH.HIDE}></span>
                      <span className={classNames(styles.onoffswitch_switch)}></span>
                    </label>
                  </div>
                </div>
              ) : null}

              <div className={classNames('clear')}></div>
            </div>
          ) : null}

          {/* Repository */}
          {ss_visible_fields.indexOf('show_source_url') > -1 ? (
            <div>
              <SubmissionFieldInput
                value={submissions_info.source_url}
                label={SUD.SUBMISSION.SOURCE_URL_LABEL}
                attribute="source_url"
                hint={source_code_hint}
                handleUpdate={this.handleUpdate}
                submission_errors={submission_errors}
              />
              {/* Repository 
                            <SubmissionFieldInput
                                value={submissions_info.fetch_repo_from_link}
                                label={SUD.SUBMISSION.REPO_LABEL}
                                attribute="fetch_repo_from_link"
                                hint={SUD.SUBMISSION.REPO_HINT}
                                handleUpdate={this.handleUpdate}
                                field_type="checkbox"

                            />
                            */}
            </div>
          ) : null}

          {/* Source Code */}
          {ss_visible_fields.indexOf('show_attachment') > -1 ? (
            <SubmissionFieldFile
              attribute="attachment"
              image_upload_state={this.state.image_upload_state}
              uploadFileOns3={this.uploadFileOns3}
              label={SUD.SUBMISSION.SOURCE_CODE_LABEL}
              hint={SUD.SUBMISSION.SOURCE_CODE_HINT}
              value={submissions_info.attachment}
              file_path={file_fields_path['attachment']}
              private_source_hint={private_source_hint}
              submission_errors={submission_errors}
            />
          ) : null}

          {/* Instructions to Run */}
          {ss_visible_fields.indexOf('show_instruction_text') > -1 ? (
            <SubmissionFieldInput
              value={submissions_info.instruction_text}
              label={SUD.SUBMISSION.INSTRUCTION_TEXT_LABEL}
              attribute="instruction_text"
              handleUpdate={this.handleUpdate}
              field_type="textarea"
              submission_errors={submission_errors}
            />
          ) : null}

          {/* Custom file field */}
          {ss_visible_fields.indexOf('show_custom_attachment') > -1 ? (
            <SubmissionFieldFile
              attribute="custom_attachment"
              image_upload_state={this.state.image_upload_state}
              uploadFileOns3={this.uploadFileOns3}
              label={submission_settings.custom_field_title}
              hint={submission_settings.custom_field_description}
              value={submissions_info.custom_attachment}
              file_path={file_fields_path['custom_attachment']}
              submission_errors={submission_errors}
            />
          ) : null}
          {submissions_info.title && !valid && mandatory_fields_left.length ? (
            <div className={classNames('warning', 'regular', styles.no_icon)}>
              <span className="">{SUD.SUBMISSION.MANDATORY_FIELD_WARNING_1}</span>
              <ol className={styles.ordered_list}>
                {mandatory_fields_left.map((field, index) => (
                  <li key={index}>{field}</li>
                ))}
              </ol>
              <span className="">{SUD.SUBMISSION.MANDATORY_FIELD_WARNING_2}</span>
            </div>
          ) : null}

          {!this.props.owner.team_info.is_team_locked ? (
            <div className="custom-checkbox">
              <input
                type="checkbox"
                value={this.state.allow_publish}
                onChange={e => {
                  let is_allowed = e.target.checked;
                  this.setState({ allow_publish: is_allowed });
                }}
              />
              <label className="dark regular">{SUD.SUBMISSION.PUBLISH_SUBMISSION_LABEL}</label>
            </div>
          ) : null}

          {this.props.event.submission_message ? (
            <div className="standard-margin panel info regular">
              <div className="bold title">{SUD.SUBMISSION.MESSAGE_FROM_ADMIN}:</div>
              <div className="subtitle" dangerouslySetInnerHTML={{ __html: this.props.event.submission_message }}></div>
            </div>
          ) : null}

          <div className="standard-margin standard-margin-bottom">
            <a
              className={classNames('button', 'btn-green', 'btn-large', 'inline-block', {
                [styles.btn_loading]: submission_btn_loading,
                [styles.btn_disabled]: submission_btn_disabled,
              })}
              onClick={!submission_btn_disabled ? this.postSubmission.bind(this) : null}>
              <span className="text">{SUD.SUBMISSION.SUBMIT}</span>
              <i className="fa fa-spinner fa-pulse"></i>
            </a>
            <div className={classNames('small', 'light', 'less-margin-2')}>{SUD.SUBMISSION.SUBMIT_HINT}</div>
          </div>
        </div>

        <div className={classNames(styles.col3, styles.right_pane, styles.fixed_div)}>
          <SprintSubmissionMandatoryChecks
            event={this.props.event}
            submissions_info={submissions_info}
            submission_settings={this.props.submission_settings}
            pagelet={this.props.pagelet}
          />
        </div>

        <div className={styles.clearfix}></div>
      </div>
    );
  }
}

class SubmissionFieldInput extends SprintComponent {
  constructor(props) {
    super(props);
  }

  render() {
    const { value, hint, label, attribute, field_type, submission_errors } = this.props;
    const has_error =
      submission_errors && submission_errors.hasOwnProperty(attribute) ? submission_errors[attribute] : '';
    return (
      <div
        className={classNames({
          [styles.styled_input]: field_type != 'checkbox',
          'custom-checkbox': field_type == 'checkbox',
          [styles.error_form]: has_error,
          [styles.half_width]: attribute == 'custom_team_id',
          'standard-margin-bottom': attribute == 'source_url',
        })}>
        {field_type === 'textarea' ? (
          <textarea
            rows="10"
            onChange={this.props.handleUpdate.bind(this, attribute)}
            placeholder={label}
            value={value}></textarea>
        ) : null}
        {field_type === 'checkbox' ? (
          <input type="checkbox" value={value} onChange={this.props.handleUpdate.bind(this, attribute)} />
        ) : null}
        {!field_type ? (
          <input
            type="text"
            value={value}
            placeholder={label}
            onChange={this.props.handleUpdate.bind(this, attribute)}
          />
        ) : null}
        <label className={classNames('dark', 'large')}>{label}</label>

        {field_type != 'checkbox' ? (
          <span className={classNames(styles.error_span)}>{SUD.IDEA.FIELD_ERROR}</span>
        ) : null}

        {hint ? (
          <div
            className={classNames('light', 'small', 'less-margin-2')}
            dangerouslySetInnerHTML={{ __html: hint }}></div>
        ) : null}
        {this.props.private_source_hint ? (
          <div
            className={classNames('light', 'small')}
            dangerouslySetInnerHTML={{ __html: this.props.private_source_hint }}></div>
        ) : null}
      </div>
    );
  }
}

class SubmissionFieldFile extends SprintComponent {
  constructor(props) {
    super(props);
  }

  render() {
    const { label, hint, attribute, value, file_path, submission_errors } = this.props;
    const src_without_sign = value ? value.split('?')[0] : '';
    const has_error =
      submission_errors && submission_errors.hasOwnProperty(attribute) ? submission_errors[attribute] : '';
    return (
      <div className={classNames(styles.form_wrapper, { [styles.error_form]: has_error })}>
        <label className={classNames('dark', 'large')}>{label}</label>
        <div>
          <div
            className={classNames(
              styles.file_upload,
              'button',
              'btn-blue',
              'inline-block',
              'btn-blue-outline',
              'less-margin-2',
            )}>
            <span> {SUD.IDEA.BROWSE}</span>
            <input
              type="file"
              name="image_upload"
              ref="file"
              className={classNames(styles.upload_input)}
              max="300"
              onChange={this.props.uploadFileOns3.bind(this, attribute)}
              disabled={this.props.image_upload_state.isUploading[attribute] ? true : false}
            />
          </div>
          {this.props.image_upload_state.isUploading[attribute] ? (
            <div className="inline-block">
              <div className={classNames(submission_styles.progress_bar_box)}>
                <div
                  className={classNames(submission_styles.progress_bar)}
                  style={{ width: this.props.image_upload_state.percentCompleted[attribute] + '%' }}></div>
              </div>
            </div>
          ) : null}
          {value ? (
            <a className={classNames('inline-block', 'dark', 'regular')} href={src_without_sign} target="_blank">
              {file_path}
            </a>
          ) : null}
        </div>
        <span className={classNames(styles.error_span)}>{SUD.IDEA.FIELD_ERROR}</span>
        {hint ? (
          <div
            className={classNames('light', 'small', 'less-margin-2')}
            dangerouslySetInnerHTML={{ __html: hint }}></div>
        ) : null}
        {this.props.private_source_hint ? (
          <div
            className={classNames('light', 'small')}
            dangerouslySetInnerHTML={{ __html: this.props.private_source_hint }}></div>
        ) : null}
      </div>
    );
  }
}


class SubmissionBodyView extends SprintComponent {
  constructor(props) {
    super(props);
    this.state = {
      viewerVisible: false,
      viewerActiveIndex: 0,
    };
  }

  render() {
    let { sprint_slug, pagelet, submissions_info } = this.props;
    console.log("SubmissionBodyView", this.props, sprint_slug, pagelet, submissions_info);
    const can_edit = !this.props.event.event_finished;
    if (this.props.pagelet != SubmissionPagelet.VIEW) return null;

    const tags = submissions_info.tags;
    const ss_visible_fields = this.props.submission_settings.visible_fields || [];
    const screenshots = submissions_info.screenshots || [];
    let images = [];
    screenshots.map(img => {
      images.push({
        original: img.screenshot ? img.screenshot.split('?')[0] : img.screenshot,
        thumbnail: img.screenshot ? img.screenshot.split('?')[0] : img.screenshot,
        id: img.id,
      });
    });

    return (
      <div className={styles.flex_column}>
        <div className={classNames(styles.col6, styles.center_pane)}>
          <h4 className="larger dark weight-400 less-margin-bottom">{SUD.SUBMISSION.HEADING}</h4>
          <div className={classNames(submission_styles.submission_nav)}>
            <div className={classNames('light', 'small', 'float-left')}>
              {SUD.SUBMISSION.LAST_UPDATED}:
              <Moment tz={this.props.timezone} locale={window.app_settings.parsed_language_code}>
                {submissions_info.last_updated}
              </Moment>
            </div>
            {can_edit ? (
              <div className={classNames('float-right', submission_styles.edit_button)}>
                <SprintLink
                  className={classNames(styles.edit_pencil, 'button', 'btn-blue-outline')}
                  to={URLManager.getEUDSubmissionPageletUrl(sprint_slug, SubmissionPagelet.EDIT)}
                  text={SUD.SUBMISSION.EDIT}
                />
              </div>
            ) : null}
            <div className={classNames('clear')}></div>
          </div>
          <div className={classNames(submission_styles.submission_view_block, 'medium-margin')}>
            <h4 className={classNames('weight-400', 'dark', 'large-18', 'medium-margin', 'less-margin-bottom')}>
              {submissions_info.title}
            </h4>
            {this.props.event.is_idea_project_submission_format && submissions_info.idea ? (
              <div className={classNames('light', 'small', 'less-margin-bottom')}>
                <span>{SUD.SUBMISSION.IDEA}: </span>
                <span>{submissions_info.idea.title}</span>
              </div>
            ) : (
              <div>
                {this.props.event.themes.length && submissions_info.theme ? (
                  <div className={classNames('light', 'small', 'less-margin-bottom')}>
                    <span>{SUD.IDEA.THEME}: </span>
                    <span>{submissions_info.theme.title}</span>
                  </div>
                ) : null}
              </div>
            )}

            {/* project details */}
            <div className={classNames(submission_styles.submission_title, 'standard-margin')}>
              <SubmissionField
                heading={SUD.SUBMISSION.DESCRIPTION_TEXT_LABEL}
                data={submissions_info.description}
                field_type="markdown"
              />
              {tags ? <SubmissionField data={tags} field_type="tags" /> : null}

              {images.length ? (
                <div className={submission_styles.screenshots}>
                  <ImageGallery items={images} slideInterval={2000} />
                </div>
              ) : null}
            </div>
            <div className={submission_styles.separator}></div>

            {/* video details */}
            {ss_visible_fields.indexOf('show_video_url') > -1 ||
            ss_visible_fields.indexOf('show_presentation') > -1 ||
            ss_visible_fields.indexOf('show_demo_link') > -1 ? (
              <div>
                <div className={classNames(submission_styles.submission_title, 'standard-margin')}>
                  <div className={classNames('large-18', 'dark', 'standard-margin-bottom')}>
                    {SUD.SUBMISSION.DEMO_HEADING}
                  </div>

                  {ss_visible_fields.indexOf('show_video_url') > -1 ? (
                    <SubmissionField heading={SUD.SUBMISSION.VIDEO} data={submissions_info.video_url} field_type="url" />
                  ) : null}

                  {ss_visible_fields.indexOf('show_presentation') > -1 ? (
                    <SubmissionField
                      heading={SUD.SUBMISSION.PRESENTATION}
                      data={submissions_info.presentation}
                      field_type="file"
                    />
                  ) : null}

                  {ss_visible_fields.indexOf('show_demo_link') > -1 ? (
                    <SubmissionField heading={SUD.SUBMISSION.DEMO} data={submissions_info.demo_link} field_type="url" />
                  ) : null}
                </div>

                <div className={submission_styles.separator}></div>
              </div>
            ) : null}

            {/* Project source */}
            {ss_visible_fields.indexOf('show_source_url') > -1 ||
            ss_visible_fields.indexOf('show_attachment') > -1 ||
            ss_visible_fields.indexOf('show_custom_attachment') > -1 ||
            ss_visible_fields.indexOf('show_instruction_text') > -1 ? (
              <div
                className={classNames(submission_styles.submission_title, 'standard-margin', 'medium-margin-bottom')}>
                <div className={classNames('large-18', 'dark', 'standard-margin-bottom')}>
                  {SUD.SUBMISSION.PROJECT_SOURCE_LABEL}
                </div>

                {ss_visible_fields.indexOf('show_source_url') > -1 ? (
                  <SubmissionField
                    heading={SUD.SUBMISSION.SOURCE_URL_LABEL}
                    data={submissions_info.source_url}
                    field_type="url"
                  />
                ) : null}

                {ss_visible_fields.indexOf('show_attachment') > -1 ? (
                  <SubmissionField
                    heading={SUD.SUBMISSION.SOURCE_CODE_LABEL}
                    data={submissions_info.attachment}
                    field_type="file"
                  />
                ) : null}

                {ss_visible_fields.indexOf('show_custom_attachment') > -1 ? (
                  <SubmissionField
                    heading={this.props.submission_settings.custom_field_title}
                    data={submissions_info.custom_attachment}
                    field_type="file"
                  />
                ) : null}

                {ss_visible_fields.indexOf('show_instruction_text') > -1 ? (
                  <SubmissionField
                    heading={SUD.SUBMISSION.INSTRUCTION_TEXT_LABEL}
                    data={submissions_info.instruction}
                    field_type="markdown"
                  />
                ) : null}
              </div>
            ) : null}
          </div>
        </div>
        <div className={classNames(styles.col3, styles.right_pane, styles.fixed_div)}>
          <SprintSubmissionMandatoryChecks
            event={this.props.event}
            submissions_info={submissions_info}
            submission_settings={this.props.submission_settings}
            pagelet={this.props.pagelet}
          />
        </div>
        <div className={styles.clearfix}></div>
      </div>
    );
  }
}

class SubmissionField extends SprintComponent {
  constructor(props) {
    super(props);
  }

  render() {
    const src_without_sign =
      this.props.field_type == 'file' && this.props.data ? this.props.data.split('?')[0] : this.props.data;
    return (
      <div className={classNames('margin-bottom-50')}>
        {this.props.field_type != 'tags' ? (
          <div
            className={classNames(
              'inline-block',
              'large',
              'dark',
              { 'less-margin-bottom': this.props.field_type !== 'markdown' },
              'bold',
            )}>
            {this.props.heading}
          </div>
        ) : null}
        {this.props.data ? (
          <div className={classNames('dark', 'regular')}>
            {this.props.field_type === 'markdown' ? (
              <span
                className={classNames(styles.description_box)}
                dangerouslySetInnerHTML={{ __html: this.props.data }}></span>
            ) : null}
            {this.props.field_type == 'title' ? <span>{this.props.data}</span> : null}
            {this.props.field_type == 'url' || this.props.field_type == 'file' ? (
              <a href={src_without_sign} target="_blank">
                {src_without_sign}
              </a>
            ) : null}
            {this.props.field_type == 'tags' ? (
              <div className="small">
                <i className="fa fa-tags light large v-align-middle"></i>
                <ul className={classNames(styles.tag_list)}>
                  {this.props.data.split(',').map((tag, index) => (
                    <li key={index}>{tag}</li>
                  ))}
                </ul>
              </div>
            ) : null}
          </div>
        ) : (
          <div className={classNames('red-text', 'large')}>{SUD.SUBMISSION.NOT_PROVIDED}</div>
        )}
      </div>
    );
  }
}

export class SprintSubmissionMandatoryChecks extends SprintComponent {
  constructor(props) {
    super(props);
  }

  render() {
    const { submissions_info, submission_settings } = this.props;
    const mandatory_fields = this.props.submission_settings.mandatory_fields || [];
    return (
      <div className={classNames('mandatory-checks-block')}>
        {submissions_info && !submissions_info.valid && this.props.pagelet == SubmissionPagelet.VIEW ? (
          <div className="standard-margin">
            <div className={classNames(styles.warning, 'regular')}>
              <i className="fa fa-warning"></i>
              <span className="bold"> {SUD.SUBMISSION.INCOMPLETE_SUBMISSION}</span>
            </div>
          </div>
        ) : null}
        <h4 className={classNames('weight-400', 'larger', 'dark', 'standard-margin', 'less-margin-bottom')}>
          {SUD.SUBMISSION.MANDATORY}
        </h4>
        <ul className={classNames(styles.checklist)}>
          <li className={classNames('light', 'large', { [styles.completed]: submissions_info.title })}>
            <i className={classNames('fa', 'fa-check')}></i>
            {SUD.SUBMISSION.TITLE}
          </li>
          {this.props.event.is_idea_project_submission_format ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.idea })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.IDEA_LABEL}
            </li>
          ) : null}

          {!this.props.event.is_idea_project_submission_format && this.props.event.themes.length ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.theme })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.IDEA.THEME}
            </li>
          ) : null}

          {mandatory_fields.indexOf('screenshots_required') > -1 ? (
            <li
              className={classNames('light', 'large', {
                [styles.completed]: submissions_info.screenshots && submissions_info.screenshots.length,
              })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.SCREENSHOTS_LABEL}
            </li>
          ) : null}

          {mandatory_fields.indexOf('video_url_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.video_url })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.VIDEO_URL_LABEL}
            </li>
          ) : null}

          {mandatory_fields.indexOf('presentation_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.presentation })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.PRESENTATION}
            </li>
          ) : null}

          {mandatory_fields.indexOf('demo_link_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.demo_link })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.DEMO_LINK_LABEL}
            </li>
          ) : null}

          {mandatory_fields.indexOf('source_url_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.source_url })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.SOURCE_URL_LABEL}
            </li>
          ) : null}

          {mandatory_fields.indexOf('attachment_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.attachment })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.SOURCE_CODE_LABEL}
            </li>
          ) : null}

          {mandatory_fields.indexOf('instruction_text_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.instruction_text })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.INSTRUCTION_TEXT_LABEL}
            </li>
          ) : null}

          {mandatory_fields.indexOf('custom_team_id_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.custom_team_id })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {SUD.SUBMISSION.TEAM_ID}
            </li>
          ) : null}

          {mandatory_fields.indexOf('custom_attachment_required') > -1 ? (
            <li className={classNames('light', 'large', { [styles.completed]: submissions_info.custom_attachment })}>
              <i className={classNames('fa', 'fa-check')}></i>
              {submission_settings.custom_field_title}
            </li>
          ) : null}
        </ul>
      </div>
    );
  }
}









































import MessageType from './constants';

import getInitialState from 'sprint/initial-state';
import { NotificationState } from 'sprint/constants';

// constant strings
const SUD = window.SUD;


export function SubmissionReducer (state=getInitialState(), message) {

    switch (message.type) {
        case MessageType.FETCH_SUBMISSION: {
            return {
                ...state
            }
        }

        case MessageType.FETCH_SUBMISSION_SUCCESS: {
            const submission_info = message.payload.data;
            //console.log(`%c FETCH_SUBMISSION_SUCCESS`,  'color: red; font-weight: bold;' ,message.payload)
            const new_state = {
                ...state,
            };

            if(submission_info.special_prizes && submission_info.special_prizes.length){
                const special_prizes = submission_info.special_prizes.map(sp => sp.id )
                submission_info.special_prizes = special_prizes;
            }

            new_state.data.submission_info = {
                ...new_state.data.submission_info,
                    ...submission_info

            }

            return new_state;
        }

        case MessageType.FETCH_SUBMISSION_FAIL: {
            return {
                ...state
            }
        }
        
        case MessageType.POST_SUBMISSION: {
            let user_loading = {
                ...state.user_loading_state[state.owner.user_id],
                submission: true,
            }
            let user_loading_state = { 
                ...state.user_loading_state, 
                [state.owner.user_id]: user_loading
            }
            return {
                ...state,
                user_loading_state
            }
        }

        case MessageType.POST_SUBMISSION_SUCCESS: {
            const submission_info = message.payload.data;
            let user_loading = {
                ...state.user_loading_state[state.owner.user_id],
                submission: false,
            }
            let user_loading_state = { 
                ...state.user_loading_state, 
                [state.owner.user_id]: user_loading
            }
            const new_state = {
                ...state,
                user_loading_state
            };

            if(submission_info.special_prizes.length){
                const special_prizes = submission_info.special_prizes.map(sp => sp.id )
                submission_info.special_prizes = special_prizes;
            }

            new_state.data.submission_info = {
                ...submission_info
            }
            return {...new_state};
        }

        case MessageType.POST_SUBMISSION_FAIL: {
            let errors = {}
            try{
                errors = message.payload.response.data || {};;
            }
            catch(err) {
                console.log(`%c status: 400 with no error.`,  'color: red; font-weight: bold;')
            }
            let error_text = errors.hasOwnProperty('error') ? `${errors.error}` : `${SUD.TEAM.SERVER_ERROR}`;


            let notification = {
                visible: true,
                state: NotificationState.ERROR,
                message: error_text

            }
            let user_loading = {
                ...state.user_loading_state[state.owner.user_id],
                submission: false,
            }
            let user_loading_state = {
                ...state.user_loading_state,
                [state.owner.user_id]: user_loading
            }
            return {
                ...state,
                user_loading_state,
                notification
            }
        }



        // SUBMISSION FIELD SETTINGS
        case MessageType.SUBMISSION_FIELD_SETTINGS: {
            return {
                ...state
            }
        }

        case MessageType.SUBMISSION_FIELD_SETTINGS_SUCCESS: {
            const submission_settings = message.payload.data;

            const new_state = {...state, submission_settings}


            return new_state;
        }

        case MessageType.SUBMISSION_FIELD_SETTINGS_FAIL: {
            return {
                ...state
            }
        }

         // Update source code visibility
        case MessageType.UPDATE_SOURCE_VISIBILITY: {
            return {
                ...state
            }
        }

        case MessageType.UPDATE_SOURCE_VISIBILITY_SUCCESS: {
            const data = message.payload;

            const new_state = {...state};

            new_state.data.submission_info = {
                ...state.data.submission_info,
                source_visibility: data.state
            }

            return new_state;
        }

        case MessageType.UPDATE_SOURCE_VISIBILITY_FAIL: {
            return {
                ...state
            }
        }

        default:
            return state

    }
}
















// constant strings
const SUD = window.SUD;



let INITIAL_STATE = {

    event: {
        id: null,
        title: null,
        slug: null,
        themes: {}, // id, title,
        team_size: null,
        min_team_size: null,
        is_idea_project_submission_format: false,
        idea_sub_start: '',
        idea_sub_started: false,
        idea_sub_finished: false,
        start: '',
        time_zone: '',
        event_started: false,
        event_finished: false,
        published_idea_limit: 0,
        is_mlh_hackathon: false,
        is_team_size_fixed: false
    },

    visible_tabs: [],

    data: {
        ideas_info: {
            sample_id: {
                id: 'sample_id',
                title: `${SUD.IDEA.SAMPLE_TITLE}`,
                description: `${SUD.IDEA.SAMPLE_DESC}`,
                description_text: `${SUD.IDEA.SAMPLE_DESC}`,
                theme: {
                    id: '',
                    title: `${SUD.IDEA.NOT_SELECTED}`
                },
                author: 'HackerEarth',
                state: '',
                attachment: '',
                //last_updated: (new Date()),
            }
        },
        teams_info: {
            // all teams info
        },
        users_info: {
            id: {
                id: null,
                full_name: 'NA',
                skills: '',
                profile_url: '',
            }
        },
        team_confirmations_info: {
            id: {
                id: null,
                user: '',
                team: '',
                invitation_type: '', //request, invite
                date: '',
                method: '', // sent or received, -> not getting from backend
                sender: '',
                status: '', //'rejected','pending','accepted','cancelled'
                user_email: '',
            }
        },
        submissions_info: {
            sample_id: {
                id: 'sample_id',
                author: 'HackerEarth',
                title : `${SUD.SUBMISSION.SAMPLE_TITLE}`,
                idea : '',
                theme : '',
                demo_link : '',
                source_url : '',
                video_url : '',
                presentation : '',
                attachment : '',
                custom_attachment : '',
                description_text: `${SUD.SUBMISSION.SAMPLE_DESC}`, //Description of the submission in sprint
                description: '',
                instruction_text: '', //Instructions to run the submission
                instruction: '',
                custom_team_id : '',
                tags : '',
                screenshots: [],
                special_prizes: [],
                fetch_repo_from_link: false,
                source_visibility: false,
                valid: false,
            }
        }
    },

    // ideas submitted/drafts listing
    ideas: {
        isLoading: false,
        published: [], //ids of idea
        draft: ['sample_id',] 
    },

    idea_slug_id_map : {
        // slug: id
    },

    submissions: {
        isLoading: false,
        published: [], //ids of submissions
        draft: ['sample_id',] 
    },

    submission_slug_id_map : {
        // slug: id
    },

    errors_data: {
        idea: {
            title: '',
            theme: '',
            description: '',
            attachment: ''
        },
        submission: {
            title : '',
            idea : '',
            theme : '',
            demo_link : '',
            source_url : '',
            video_url : '',
            presentation : '',
            attachment : '',
            custom_attachment : '',
            description_text: '', 
            instruction_text: '', 
            special_prizes : '',
            custom_team_id : '',
            tags : '',
            screenshots: '',
        },
    },

    // details of the current logged in user
    owner: {
        user_id: null,
        team_id: null,
        intent: null,
        team_role: null,
        timezone: '',
        team_info: {
            id: null,
            handle: '',
            slug: '',
            synopsis: '',
            teammates: false,
            users: [],
            primary_user: '',
            is_team_locked: false,
            is_team_info_saving: false
        }
    },

    // data of invites/requests for owner's team
    // in case of T=1, there will be invites from other teams
    // in case of T=2, there will be no invites from other teams
    team_confirmations: {
        isLoading: true,
        join_requests: {
            //team_id: confirmation_id,
        }, 
        invites: {
            //user_id: confirmation_id,
        }
    },
    // seperate the JR and Invites:
    // JR: all the jr sent and received by onwer as user
    // invites: all the invites sent & received by owner as team 
    team_confirmations_filtered: {
        join_request: [],
        invite: []
    },

    // users who can be invited by the current user/team
    users_to_invite: {
        isLoading: true,
        ids: [ ],
        hasMoreParticipants: true,
        nextPageIndex: 1,
    },

    // teams the current user can join
    teams_to_join: {
        isLoading: true,
        ids: [],
        hasMoreTeams: true,
        nextPageIndex: 1,
    },

    // temporary images
    temp_images_paths : [],

    submission_settings: {
        custom_field_title: '',
        custom_field_description: '',
        visible_fields: [],
        mandatory_fields: [],
        special_prizes: [],
        shortlisted_ideas: [],
        mlh_hardwares_json: [],
    },

    
    // loading params
    // is loading is for loading 
    // other params shows which one to load
    user_loading_state: {
        0: {
            is_loading: false,
            //[TeamMemberAction]: false, leave/remove
            //[IdeaListingType]: false: draft, publish
            submission: false,
            //[TeamConfirmationType] : false,
            //[TeamConfirmationStatus]: false

        }
    },

    notification: {
        visible: false,
        state: '', // success/error
        message: '',// text to be shown,
    },

    invite_email: {
        email: '',
        message: `${SUD.TEAM.INVITE_MESSAGE}`,
        error: '',
    }

};

export default function getInitialState(hydration_data){

    let state = {};
    state = {...INITIAL_STATE};

    if (hydration_data) {
        state = {...state, ...hydration_data };
    }

    return state;

}



















export const IdeaListingType = {
    SUBMITTED: 'published',
    DRAFT: 'draft',
    NEW: 'new',
    SAMPLE: 'sample',
}

export const SubmissionListingType = {
    SUBMITTED: 'published',
    DRAFT: 'draft',
    NEW: 'new',
    SAMPLE: 'sample',
}


export const PageSegment = {
    SUBMISSION: 'submission',
    IDEA: 'idea',
    TEAM: 'team',
    TEAM_LISTING: 'team-listing',

}

export const TeamPagelet = {
    VIEW: 'view',
    EDIT: 'edit',
    INVITE: 'invite',
    INVITE_EMAIL: 'invite-email',
}

export const SubmissionPagelet = {
    VIEW: 'view',
    EDIT: 'edit',
}

export const PageletState = {
    VIEW: 'view',
    EDIT: 'edit',
}


export const TeamConfirmationType = {
    REQUEST: 'join_request',
    INVITE: 'invite'
}

export const TeamConfirmationMethod = {
    SENT: 'sent',
    RECEIVED: 'received'
}

export const TeamConfirmationSender = {
    USER: 'user',
    TEAM: 'team'
}

export const OwnerIntent = {
    USER: 'user',
    TEAM: 'team'
}

export const TeamRole = {
    LEADER: 'leader',
    MEMBER: 'member'
}

export const TeamMemberAction = {
    LEAVE: 'leave',
    REMOVE: 'remove'
}

export const TeamConfirmationStatus = {
    REJECTED: 'rejected',
    PENDING: 'pending',
    ACCEPTED: 'accepted',
    CANCELLED: 'cancelled'
}

export const EvaluationState = {
    UNEVALUATED: "unevaluated",
    ACCEPTED: "shortlisted",
    REJECTED: "not_shortlisted"
}

export const NotificationState = {
    SUCCESS: 'success',
    ERROR: 'error'
}

export const CSRFHeader = {
    headers: {
        "X-CSRFToken": csrftoken
    }
}

























import { PageSegment } from 'sprint/constants';


const DEFAULT_PARAMS = {
    SPRINT_SLUG: ':sprint_slug',
    TEAM_SLUG: ':team_slug',
    PAGE_SEGMENT: ':page_segment',
    PAGELET: ':pagelet',
    IDEA_LISTING_TYPE: ':idea_listing_type',
    SUBMISSION_LISTING_TYPE: ':submission_listing_type',
    PAGELET_ID: ':pagelet_id',
    TEAM_PAGELET: ':team_pagelet',
    SUBMISSION_PAGELET: ':submission_pagelet',
    PAGELET_STATE: ':pagelet_state',
}

{/* All strings defined within `xxx` are ES6 template strings.
    Please refer to appropriate documentation before thinking
    about changing them single/double quotes.

    The functions defined in URLManager return parametrized urls
    if no function parameters are provided. These urls are used to
    specify route definitions in routes.js.

    If func parameters are provided, the urls returned are suitable
    for linking components deep inside the circles app.
*/}

export class BaseURLManager {

    setLanguageSlug(slug){
        BaseURLManager.LANGUAGE_SLUG = slug;
    }

    static getBaseSprintURL(){
        let url = `/challenges/hackathon/`;

        let language_slug = window.app_settings.LANGUAGE_SLUG; //window.app_settings.LANGUAGE_SLUG;
        if (language_slug){
            url = `/` + language_slug + url;
        }
        return url;
    }
}


export class URLManager {
    static getSprintsUrl(){
        let url = BaseURLManager.getBaseSprintURL();
        return url;
    }

    static getEventUrl(sprint_slug) {
        sprint_slug = sprint_slug || DEFAULT_PARAMS.SPRINT_SLUG;
        let url = BaseURLManager.getBaseSprintURL() + `${sprint_slug}/`
        return url;
    }

    static getEUDashboardUrl(sprint_slug){
        // EUD -> Event User Dashboard
        sprint_slug = sprint_slug || DEFAULT_PARAMS.SPRINT_SLUG;
        let url = BaseURLManager.getBaseSprintURL() + `${sprint_slug}/dashboard/`;
        return url;
    }

    static getEUDUrl(sprint_slug, team_slug){
        // EUD -> Event User Dashboard
        sprint_slug = sprint_slug || DEFAULT_PARAMS.SPRINT_SLUG;
        team_slug = team_slug || window.app_settings.team_slug || DEFAULT_PARAMS.TEAM_SLUG;
        let url = BaseURLManager.getBaseSprintURL() + `${sprint_slug}/dashboard/${team_slug}/`;
        return url;
    }

    static getEUDPageSegmentUrl(sprint_slug, page_segment){
        page_segment = page_segment || DEFAULT_PARAMS.PAGE_SEGMENT;
        let url = URLManager.getEUDUrl(sprint_slug) + `${page_segment}/`;
        return url;
    }

    static getEUDSubmissionRootUrl(sprint_slug){
        let url = URLManager.getEUDPageSegmentUrl(sprint_slug, PageSegment.SUBMISSION);
        return url;
    }

    static getEUDIdeaListingRootUrl(sprint_slug){
        let url = URLManager.getEUDPageSegmentUrl(sprint_slug, PageSegment.IDEA);
        return url;
    }


    static getEUDTeamManagementRootUrl(sprint_slug){
        let url = URLManager.getEUDPageSegmentUrl(sprint_slug, PageSegment.TEAM);
        return url;
    }

    static getEUDTeamListingRootUrl(sprint_slug){
        let url = URLManager.getEUDPageSegmentUrl(sprint_slug, PageSegment.TEAM_LISTING);
        return url;
    }

    static getEUDPageletUrl(sprint_slug, page_segment, pagelet){
        pagelet = pagelet || DEFAULT_PARAMS.PAGELET;
        let url = URLManager.getEUDPageSegmentUrl(sprint_slug, page_segment) + `${pagelet}/`;
        return url;
    }

    static getEUDIdeaListingUrl(sprint_slug, idea_listing_type){
        idea_listing_type = idea_listing_type || DEFAULT_PARAMS.IDEA_LISTING_TYPE;
        let url = URLManager.getEUDIdeaListingRootUrl(sprint_slug) + `${idea_listing_type}/`;
        return url;
    }

    static getEUDSubmissionListingUrl(sprint_slug, submission_listing_type){
        submission_listing_type = submission_listing_type || DEFAULT_PARAMS.SUBMISSION_LISTING_TYPE;
        let url = URLManager.getEUDSubmissionRootUrl(sprint_slug) + `${submission_listing_type}/`;
        return url;
    }

    static getEUDPageletIdUrl(sprint_slug, page_segment, pagelet, pagelet_id){
        pagelet_id = pagelet_id || DEFAULT_PARAMS.PAGELET_ID;
        let url = URLManager.getEUDPageletUrl(sprint_slug, page_segment, pagelet) + `${pagelet_id}/`;
        return url;
    }

    static getEUDPageletStateUrl(sprint_slug, page_segment, pagelet, pagelet_id, pagelet_state){
        pagelet_state = pagelet_state || DEFAULT_PARAMS.PAGELET_STATE;
        let url = URLManager.getEUDPageletIdUrl(sprint_slug, page_segment, pagelet, pagelet_id) + `${pagelet_state}/`;
        return url;
    }

    static getEUDTeamPageletUrl(sprint_slug, team_pagelet){
        team_pagelet = team_pagelet || DEFAULT_PARAMS.TEAM_PAGELET;
        let url = URLManager.getEUDTeamManagementRootUrl(sprint_slug) + `${team_pagelet}/`;
        return url;
    }

    static getEUDSubmissionPageletUrl(sprint_slug, submission_pagelet){
        submission_pagelet = submission_pagelet || DEFAULT_PARAMS.SUBMISSION_PAGELET;
        let url = URLManager.getEUDSubmissionRootUrl(sprint_slug) + `${submission_pagelet}/`;
        return url;
    }

}


const event_id = window.app_settings.event_id;
const team_id = window.app_settings.team_id;

export class ApiURLManager{



    static fetchIdeasUrl(id) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/ideas/`;
        if(id) {
            url += `idea/${id}/`
        }
        return url;
    }

    static fetchTeamsUrl() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/teams/`;
        return url;
    }

    static fetchAllUsersUrl() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/participants/`;
        return url;
    }

    static fetchUsersToInvitesUrl() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/participants/`;
        return url;
    }

    
    static fetchTeamInfoUrl() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/teams/${team_id}/`;
        return url;
    }

    static saveTeamDetail() {
        let url = BaseURLManager.getBaseSprintURL() + `api/team/`;
        return url;
    }


    static requestInviteMember(id) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/invitations/invite/`;
        if(id) {
            url += `${id}/`;
        }

        return url;
    }
    static requestJoinTeam(id) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/invitations/join/`;

        if(id) {
            url += `${id}/`;
        }

        return url;

    }
    static fetchTeamConfirmation() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/invitations/`;
        return url;
    }



    static fetchSubmissionUrl(team_id) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/submissions/?team_id=${team_id}`;
        return url;
    }

    static postSubmissionUrl(id) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/submissions/`;
        if(id) { url += `${id}/`; }
        return url;
    }
    // image upload for temporary images
    // delete this
    static uploadImageURL() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/upload-url/`;
        return url;
    }

    // to upload files on s3
    // get with params to create s3 signed url
    // put request to upload file
    static prefetchSignedURl() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/upload-url/`;
        return url;
    }

    static postIdea(idea_id) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/ideas/idea/`;

        return url;
    }

    static submissionFieldSettings() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/submission-field-settings/${team_id}/`;
        return url;
    }

    // remove/ leave team
    static removeTeamMember(member_id, action) {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/teams/${team_id}/member/${member_id}/?action=${action}`;

        return url;
    }

    static createSubmissionScreenshot() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/submissions/screenshot/`;

        return url;
    }

    static updateSourecVisibility() {
        let url = BaseURLManager.getBaseSprintURL() + `api/v1/event/${event_id}/submissions/update-source-visibility/${team_id}/`;

        return url;
    }




}


export class StaticURLManager{
    static getBaseImageURL(){
        return window.app_settings.STATIC_URL + 'sprints/images/' ;
    }

    static getImageURL(image_name){
        return StaticURLManager.getBaseImageURL() + image_name;
    }

    static getShortlistedImageURL(){
        return StaticURLManager.getBaseImageURL() + "shortlisted.png";
    }

    static getNotShortlistedImageURL(){
        return StaticURLManager.getBaseImageURL() + "not_shortlisted.png";
    }

    static defaultImage() {
        return window.app_settings.STATIC_URL + 'base/images/gravatar.png';
    }

}

